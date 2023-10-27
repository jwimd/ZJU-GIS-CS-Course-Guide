#include "trap.h"
#include "types.h"
#include "clock.h"
#include "printk.h"
#include "proc.h"
#include "syscall.h"

// scause trap类型 sepc trap发生的地址
void trap_handler(uint64 scause, uint64 sepc, struct pt_regs *regs)
{
    // printk("kernel is running!\n"); //指示操作系统陷阱机制运行的输出

    uint64 interrupt_sign = scause >> 63;         //获取最高位（interrupt指示位）的值
    uint64 trap_type = (scause << 1) >> 1; //获取最低4位（interrupt类型指示位）的值

    if (interrupt_sign) // interrupt
    {
        switch (trap_type)
        {
        case 5:
            //printk("[S] Supervisor Mode Timer Interrupt\n"); //指示发生时钟中断的输出

            do_timer();

            clock_set_next_event();
            break;
        default:
            break;
        }
    }
    else // exception
    {
        switch (trap_type)
        {
        case 8: // Environment call from U-mode
            switch (regs->a7)
            {
            case SYS_WRITE:
                regs->a0 = sys_write(regs->a0, regs->a1, regs->a2);
                break;
            case SYS_GETPID:
                regs->a0 = sys_getpid();
                break;

            default:
                break;
            }

            regs->sepc += 4; //使sepc返回异常触发的后一条指令
            break;
        default:
            break;
        }
    }

    return;
}