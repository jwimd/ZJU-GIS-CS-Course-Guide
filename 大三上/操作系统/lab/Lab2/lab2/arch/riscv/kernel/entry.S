.extern trap_handler
    
    .section .text.entry   #text的entry部分，在init部分后执行
    .align 2#两字节对齐
    .globl _traps 
_traps:
    
    #该段将32个寄存器和spec的值写入栈中，每个寄存器64位，并随时更新栈顶的地址
    addi sp, sp, -33*16
    sd zero, 0*16(sp)
    sd ra, 1*16(sp)
    sd gp, 2*16(sp)
    sd tp, 3*16(sp)
    sd t0, 4*16(sp)
    sd t1, 5*16(sp)
    sd t2, 6*16(sp)
    sd s0, 7*16(sp)
    sd s1, 8*16(sp)
    sd a0, 9*16(sp)
    sd a1, 31*16(sp)
    sd a2, 10*16(sp)
    sd a3, 11*16(sp)
    sd a4, 12*16(sp)
    sd a5, 13*16(sp)
    sd a6, 14*16(sp)
    sd a7, 15*16(sp)
    sd s2, 16*16(sp)
    sd s3, 17*16(sp)
    sd s4, 18*16(sp)
    sd s5, 19*16(sp)
    sd s6, 20*16(sp)
    sd s7, 21*16(sp)
    sd s8, 22*16(sp)
    sd s9, 23*16(sp)
    sd s10, 24*16(sp)
    sd s11, 25*16(sp)
    sd t3, 26*16(sp)
    sd t4, 27*16(sp)
    sd t5, 28*16(sp)
    sd t6, 29*16(sp)
    csrr t0, sepc
    sd t0, 30*16(sp)
    sd sp, 32*16(sp)

    # 调用trap_handler启动陷阱事件
    csrr a0, scause
    csrr a1, sepc
    call trap_handler

    #将32个寄存器和spec的值从栈中读取
    ld t0, 30*16(sp)
    csrw sepc, t0
    ld zero, 0*16(sp)
    ld ra, 1*16(sp)
    ld gp, 2*16(sp)
    ld tp, 3*16(sp)
    ld t0, 4*16(sp)
    ld t1, 5*16(sp)
    ld t2, 6*16(sp)
    ld s0, 7*16(sp)
    ld s1, 8*16(sp)
    ld a0, 9*16(sp)
    ld a1, 31*16(sp)
    ld a2, 10*16(sp)
    ld a3, 11*16(sp)
    ld a4, 12*16(sp)
    ld a5, 13*16(sp)
    ld a6, 14*16(sp)
    ld a7, 15*16(sp)
    ld s2, 16*16(sp)
    ld s3, 17*16(sp)
    ld s4, 18*16(sp)
    ld s5, 19*16(sp)
    ld s6, 20*16(sp)
    ld s7, 21*16(sp)
    ld s8, 22*16(sp)
    ld s9, 23*16(sp)
    ld s10, 24*16(sp)
    ld s11, 25*16(sp)
    ld t3, 26*16(sp)
    ld t4, 27*16(sp)
    ld t5, 28*16(sp)
    ld t6, 29*16(sp)
    ld sp, 32*16(sp)
    addi sp, sp, 33*16

    sret #一定要用sret返回sepc地址！！！