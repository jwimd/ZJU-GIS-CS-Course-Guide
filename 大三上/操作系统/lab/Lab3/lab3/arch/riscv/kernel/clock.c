#include "clock.h"
#include "types.h"
#include "sbi.h"

uint64 TIMECLOCK = 10000000;

uint64 get_cycles()
{
    register uint64 time = 0;
    __asm__ volatile(
        "rdtime %[time]\n"

        : [time] "=r"(time)

        :

        : "memory");

    return time;
}

void clock_set_next_event()
{
    // 下一次 时钟中断 的时间点
    uint64 next = get_cycles() + TIMECLOCK;

    sbi_ecall(0x0, 0x00, next, 0, 0, 0, 0, 0); //调用ecall

    return;
}