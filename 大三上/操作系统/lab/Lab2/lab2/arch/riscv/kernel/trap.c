#include "trap.h"
#include "types.h"
#include "printk.h"

// scause trap类型 sepc trap发生的地址
void trap_handler(uint64 scause, uint64 sepc)
{
    printk("kernel is running!\n"); //指示操作系统陷阱机制运行的输出

    uint64 interrupt_sign = scause >> 63;         //获取最高位（interrupt指示位）的值
    uint64 interrupt_type = (scause << 60) >> 60; //获取最低4位（interrupt类型指示位）的值

    if (interrupt_sign) // interrupt
    {
        switch (interrupt_type)
        {
        case 5:
            printk("[S] Supervisor Mode Timer Interrupt\n"); //指示发生时钟中断的输出
            clock_set_next_event();
            break;
        default:
            break;
        }
    }
    else // exception
    {
    }

    return;
}