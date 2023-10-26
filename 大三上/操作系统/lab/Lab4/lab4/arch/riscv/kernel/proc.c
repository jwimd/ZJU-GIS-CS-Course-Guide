// arch/riscv/kernel/proc.c
#include "proc.h"
#include "printk.h"
#include "mm.h"
#include "rand.h"
#include "defs.h"

extern char _srodata[];

extern void __dummy();

struct task_struct *idle;           // idle process
struct task_struct *current;        // 指向当前运行线程的 `task_struct`
struct task_struct *task[NR_TASKS]; // 线程数组, 所有的线程都保存在此

void task_init()
{
    idle = (struct task_struct *)kalloc();
    // 调用 kalloc() 为 idle 分配一个物理页

    idle->state = TASK_RUNNING;
    // 设置 state 为 TASK_RUNNING;

    idle->counter = 0;
    idle->counter = PRIORITY_IDLE;
    // 由于 idle 不参与调度 可以将其 counter / priority 设置为 0

    idle->pid = 0;
    // 设置 idle 的 pid 为 0

    current = idle;
    task[0] = idle;

    // 为 task[1] ~ task[NR_TASKS - 1] 设置 `thread_struct` 中的 `ra` 和 `sp`,
    // 其中 `ra` 设置为 __dummy的地址,  `sp` 设置为 该线程申请的物理页的高地址

    int i = 0;
    for (i = 1; i < NR_TASKS; ++i)
    {
        task[i] = (struct task_struct *)kalloc();

        task[i]->state = TASK_RUNNING;

        task[i]->counter = 0;
        task[i]->priority = rand();

        task[i]->pid = i;

        task[i]->thread.ra = (uint64)&__dummy;
        task[i]->thread.sp = (uint64)task[i] + PGSIZE;
    }

    printk("...proc_init done!\n");
    printk("Hello RISC-V\n");
    printk("idle process is running!\n");
    printk("\n");

    reset_thread();

    return;
}

void dummy()
{
    uint64 MOD = 1000000007;
    uint64 auto_inc_local_var = 0;
    int last_counter = -1;
    while (1)
    {
        if (last_counter == -1 || current->counter != last_counter)
        {
            last_counter = current->counter;
            auto_inc_local_var = (auto_inc_local_var + 1) % MOD;
            printk("[PID = %d] is running. Thread space begin at 0x%lx\n", current->pid, current);
            printk("%d", *((uint64 *)_srodata)); // read text
            *((uint64 *)_srodata) = 1;           // write text
            printk("%d", *((uint64 *)_srodata));
        }
    }

    return;
}

extern void __switch_to(struct task_struct *prev, struct task_struct *next);

void do_timer(void)
{
    // 如果当前线程是 idle 线程 直接进行调度
    if (current->pid == 0)
        schedule();

    // 如果当前线程不是 idle 对当前线程的运行剩余时间减1 若剩余时间仍然大于0 则直接返回 否则进行调度
    else
    {
        current->counter--;
        if (current->counter > 0)
            return;
        else
            schedule();
    }
    return;
}

#ifdef SJF
void switch_to(struct task_struct *next)
{
    if (next->pid == current->pid)
        return;

    printk("\n");
    printk("switch to [PID = %d COUNTER = %d]\n", next->pid, next->counter);
    __switch_to(current, next);
}

void schedule(void)
{
    int i = 0;
    int to_execute = -1;

    int to_reset = 1;

    for (i = 1; i < NR_TASKS; i++)
    {
        if (task[i]->state != TASK_RUNNING)
            continue;
        if (task[i]->counter > 0)
            to_reset = 0;
        else
            continue;
        if (to_execute == -1 || task[i]->counter < task[to_execute]->counter)
            to_execute = i;
    }

    if (to_reset == 1)
    {
        reset_thread();
        schedule();
        return;
    }

    switch_to(task[to_execute]);

    return;
}

void reset_thread()
{
    int i = 0;

    printk("\n");

    for (i = 1; i < NR_TASKS; ++i)
    {
        task[i]->counter = rand();
        printk("SET [PID = %d COUNTER = %d]\n", task[i]->pid, task[i]->counter);
    }

    printk("\n");
    return;
}
#endif

#ifdef PRIORITY
void switch_to(struct task_struct *next)
{
    if (next->pid == current->pid)
        return;

    printk("\n");
    printk("switch to [PID = %d PRIORITY = %d COUNTER = %d]\n", next->pid, next->priority, next->counter);
    __switch_to(current, next);
}

void schedule(void)
{
    int i, next, c;
    struct task_struct **p;

    c = -1;
    next = 0;
    i = NR_TASKS;
    p = &task[NR_TASKS];

    while (--i)
    {
        if (!*--p)
            continue;
        if (((*p)->state == TASK_RUNNING) && ((int)(*p)->counter > c))
        {
            c = (*p)->counter;
            next = i;
        }
    }

    if (!c)
    {
        reset_thread();
        schedule();
        return;
    }

    switch_to(task[next]);
    return;
}

void reset_thread()
{
    struct task_struct **p;

    printk("\n");

    for (p = &task[1]; p < &task[NR_TASKS]; ++p)
        if (*p)
        {
            (*p)->counter = ((*p)->counter >> 1) + (*p)->priority;
            printk("SET [PID = %d PRIORITY = %d COUNTER = %d]\n", (*p)->pid, (*p)->priority, (*p)->counter);
        }

    return;

    printk("\n");
}
#endif