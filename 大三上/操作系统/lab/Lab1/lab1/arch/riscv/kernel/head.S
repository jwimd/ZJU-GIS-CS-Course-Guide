.extern start_kernel #外部引入入口函数start_kernel

    .section .text.entry #指示改部分是text部分的entry
    .globl _start #定义start为全局标签
_start:
    la sp, boot_stack_top #将栈指针寄存器指向栈顶地址
    j start_kernel #跳跃到函数入口的地址


    .section .bss.stack
    .globl boot_stack
boot_stack:
    .space 0x4000 #分配栈空间4k

    .globl boot_stack_top
boot_stack_top: