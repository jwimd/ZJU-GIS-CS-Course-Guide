#.extern trap_handler
#.extern dummy
#.extern current
#include "defs.h"
    
    .section .text.entry   #text的entry部分，在init部分后执行
    .align 2#两字节对齐
    .globl _traps 
_traps:
    sd t0, -8(sp)
    addi sp, sp, -8
    csrr t0, sscratch
    beqz t0, _traps_skip_one
    #转换到U mode的stack，交换运行栈指针
    #栈指针切换，如果是内核线程不需要切换栈指针
    csrw sscratch, sp
    add sp, zero, t0

_traps_skip_one:
    #该段将32个寄存器和spec的值写入栈中，每个寄存器64位，并随时更新栈顶的地址
    addi sp, sp, -33*8
    sd zero, 0*8(sp)
    sd ra, 1*8(sp)
    sd gp, 2*8(sp)
    sd tp, 3*8(sp)
    sd t0, 4*8(sp)
    sd t1, 5*8(sp)
    sd t2, 6*8(sp)
    sd s0, 7*8(sp)
    sd s1, 8*8(sp)
    sd a0, 9*8(sp)
    sd a1, 10*8(sp)
    sd a2, 11*8(sp)
    sd a3, 12*8(sp)
    sd a4, 13*8(sp)
    sd a5, 14*8(sp)
    sd a6, 15*8(sp)
    sd a7, 16*8(sp)
    sd s2, 17*8(sp)
    sd s3, 18*8(sp)
    sd s4, 19*8(sp)
    sd s5, 20*8(sp)
    sd s6, 21*8(sp)
    sd s7, 22*8(sp)
    sd s8, 23*8(sp)
    sd s9, 24*8(sp)
    sd s10, 25*8(sp)
    sd s11, 26*8(sp)
    sd t3, 27*8(sp)
    sd t4, 28*8(sp)
    sd t5, 29*8(sp)
    sd t6, 30*8(sp)
    csrr t0, sepc
    sd t0, 31*8(sp)
    sd sp, 32*8(sp)

    # 调用trap_handler启动陷阱事件
    csrr a0, scause
    csrr a1, sepc
    add a2, sp, zero
    call trap_handler

    #将32个寄存器和spec的值从栈中读取
    ld t0, 31*8(sp)
    csrw sepc, t0
    ld zero, 0*8(sp)
    ld ra, 1*8(sp)
    ld gp, 2*8(sp)
    ld tp, 3*8(sp)
    ld t0, 4*8(sp)
    ld t1, 5*8(sp)
    ld t2, 6*8(sp)
    ld s0, 7*8(sp)
    ld s1, 8*8(sp)
    ld a0, 9*8(sp)
    ld a1, 10*8(sp)
    ld a2, 11*8(sp)
    ld a3, 12*8(sp)
    ld a4, 13*8(sp)
    ld a5, 14*8(sp)
    ld a6, 15*8(sp)
    ld a7, 16*8(sp)
    ld s2, 17*8(sp)
    ld s3, 18*8(sp)
    ld s4, 19*8(sp)
    ld s5, 20*8(sp)
    ld s6, 21*8(sp)
    ld s7, 22*8(sp)
    ld s8, 23*8(sp)
    ld s9, 24*8(sp)
    ld s10, 25*8(sp)
    ld s11, 26*8(sp)
    ld t3, 27*8(sp)
    ld t4, 28*8(sp)
    ld t5, 29*8(sp)
    ld t6, 30*8(sp)
    ld sp, 32*8(sp)
    addi sp, sp, 33*8

    csrr t0, sscratch
    beqz t0, _traps_skip_two
    #转换到U mode的stack，交换运行栈指针
    #栈指针切换，如果是内核线程不需要切换栈指针
    csrw sscratch, sp
    add sp, zero, t0
    ld t0, 0(sp)
    addi sp, sp, 8

_traps_skip_two:
    sret #一定要用sret返回sepc地址！！！

    .global __dummy
__dummy:
    #转换到U mode的stack，交换运行栈指针
    csrr t0, sscratch
    csrw sscratch, sp
    add sp, zero, t0

    #la t0, dummy
    #csrw sepc, t0
    sret

    .globl __switch_to
__switch_to:
    # save state to prev process
    sd ra, 8*5(a0)
    sd sp, 8*6(a0)
    sd s0, 8*7(a0)
    sd s1, 8*8(a0)
    sd s2, 8*9(a0)
    sd s3, 8*10(a0)
    sd s4, 8*11(a0)
    sd s5, 8*12(a0)
    sd s6, 8*13(a0)
    sd s7, 8*14(a0)
    sd s8, 8*15(a0)
    sd s9, 8*16(a0)
    sd s10, 8*17(a0)
    sd s11, 8*18(a0)
    csrr t0, sepc
    sd t0, 8*19(a0)
    csrr t0, sstatus
    sd t0, 8*20(a0)
    csrr t0, sscratch
    sd t0, 8*21(a0)

    # restore state from next process
    ld ra, 8*5(a1)
    ld sp, 8*6(a1)
    ld s0, 8*7(a1)
    ld s1, 8*8(a1)
    ld s2, 8*9(a1)
    ld s3, 8*10(a1)
    ld s4, 8*11(a1)
    ld s5, 8*12(a1)
    ld s6, 8*13(a1)
    ld s7, 8*14(a1)
    ld s8, 8*15(a1)
    ld s9, 8*16(a1)
    ld s10, 8*17(a1)
    ld s11, 8*18(a1)
    ld t0, 8*19(a1)
    csrw sepc, t0
    ld t0, 8*20(a1)
    csrw sstatus, t0
    ld t0, 8*21(a1)
    csrw sscratch, t0

    #切换页表
    li t0, 0x8000000000000000
    ld t1, 8*22(a1)
    li t2, PA2VA_OFFSET
    sub t1, t1, t2
    srl t1, t1, 12
    add t0, t0, t1

    csrw satp, t0

    # flush tlb
    sfence.vma zero, zero

    # flush icache
    fence.i

    #指针移动
    la t0, current
    sd a1, 0(t0)

    ret