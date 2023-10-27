#include "syscall.h"
#include "types.h"
#include "stddef.h"
#include "stdint.h"
#include "sbi.h"
#include "proc.h"

extern struct task_struct *current;

uint64_t sys_write(unsigned int fd, const char *buf, size_t count)
{
    int i = 0;
    uint64 output_count = 0;

    for (i = 0; i < count; i++)
    {
        sbi_ecall(fd, 0, (uint64) * (buf + i), 0, 0, 0, 0, 0);
        output_count++;
    }

    return output_count;
}

uint64_t sys_getpid()
{
    return (uint64)current->pid;
}