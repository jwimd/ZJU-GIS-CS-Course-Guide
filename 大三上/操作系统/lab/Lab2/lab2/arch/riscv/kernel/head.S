.extern start_kernel #外部引入入口函数start_kernel
.extern sbi_ecall #外部引入系统调用函数

    .section .text.init 
    .globl _start #定义start为全局标签
_start:

    la sp, boot_stack_top #将栈指针寄存器指向栈顶地址

    # 将_traps的地址写入stvec
    la t0, _traps
    csrw stvec, t0

    # 设置 sie[STIE] = 1 是s-mode下时钟中断enable比特位, 启动时钟中断
    csrr t0, sie
    ori t0, t0, 32
    csrw sie, t0

    # 调用c函数sbi_ecall，使用opensbi设置第一次时钟中断时间为当前时间
    li a0, 0x00
    li a1, 0x0
    rdtime a2
    li a3, 0x0
    li a4, 0x0
    li a5, 0x0
    li a6, 0x0
    li a7, 0x0
    call sbi_ecall

    # 设置 sstatus[SIE] = 1, 在S-mode下开启所有中断
    csrr t0, sstatus
    ori t0, t0, 2
    csrw sstatus, t0

    j start_kernel #跳跃到函数入口的地址


    .section .bss.stack
    .globl boot_stack
boot_stack:
    .space 0x4000 #分配栈空间4k

    .globl boot_stack_top
boot_stack_top: