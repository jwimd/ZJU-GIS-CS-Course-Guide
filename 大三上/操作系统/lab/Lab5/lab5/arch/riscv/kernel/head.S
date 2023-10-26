#include "defs.h"

    .section .text.init 
    .globl _start #定义start为全局标签
_start:
    la t0, boot_stack_top
    li t1, PA2VA_OFFSET
    sub sp, t0, t1 #指向物理地址栈顶，便于setup_vm函数执行
    
    call setup_vm
    call relocate

    la sp, boot_stack_top #将栈指针寄存器指向栈顶地址

    call mm_init
    call setup_vm_final

    call task_init

    # 将_traps的地址写入stvec
    la t0, _traps
    csrw stvec, t0

    # 设置 sie[STIE] = 1 是s-mode下时钟中断enable比特位, 启动时钟中断
    csrr t0, sie
    ori t0, t0, 32
    csrw sie, t0

    # 调用c函数sbi_ecall，使用opensbi设置第一次时钟中断时间为当前时间
    li a0, 0x0
    li a1, 0x0
    rdtime a2
    li a3, 0x0
    li a4, 0x0
    li a5, 0x0
    li a6, 0x0
    li a7, 0x0
    call sbi_ecall

    # 设置 sstatus[SIE] = 1, 在S-mode下开启所有中断
    #csrr t0, sstatus
    #ori t0, t0, 2
    #csrw sstatus, t0

    j start_kernel #跳跃到函数入口的地址

relocate:
    # set ra = ra + PA2VA_OFFSET
    # set sp = sp + PA2VA_OFFSET (If you have set the sp before)

    li t0, PA2VA_OFFSET
    add ra, ra, t0
    add sp, sp, t0

    # set satp with early_pgtbl

    li t0, 0x8000000000000000
    la t1, early_pgtbl
    li t2, PA2VA_OFFSET
    sub t1, t1, t2
    srl t1, t1, 12
    add t0, t0, t1

    csrw satp, t0

    # flush tlb
    sfence.vma zero, zero

    # flush icache
    fence.i

    ret

    .section .bss.stack
    .globl boot_stack
boot_stack:
    .space 0x1000 #分配栈空间4k

    .globl boot_stack_top
boot_stack_top: