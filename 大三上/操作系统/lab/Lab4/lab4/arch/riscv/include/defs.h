#ifndef _DEFS_H
#define _DEFS_H

#define csr_read(csr)       \
    ({                      \
        uint64 __v;         \
        asm volatile(       \
            "csrr %0," #csr \
            : "=r"(__v)     \
            :               \
            : "memory");    \
        __v;                \
    })

#define csr_write(csr, val)         \
    ({                              \
        uint64 __v = (uint64)(val); \
        asm volatile(               \
            "csrw " #csr ", %0"     \
            :                       \
            : "r"(__v)              \
            : "memory");            \
    })

#define PHY_START 0x0000000080000000
#define PHY_SIZE 128 * 1024 * 1024 // 128MB,  QEMU 默认内存大小
#define PHY_END (PHY_START + PHY_SIZE)

#define PGSIZE_2LEVEL 0x40000000 // 1GB
#define PGSIZE_1LEVEL 0x200000   // 2MB
#define PGSIZE 0x1000            // 4KB

#define PGROUNDUP(addr) ((addr + PGSIZE - 1) & (~(PGSIZE - 1)))
#define PGROUNDDOWN(addr) (addr & (~(PGSIZE - 1)))

#define OPENSBI_SIZE (0x200000)

#define VM_START (0xffffffe000000000)
#define VM_END (0xffffffff00000000)
#define VM_KERNEL_END (VM_START + PHY_SIZE)
#define VM_SIZE (VM_END - VM_START)

#define PA2VA_OFFSET (VM_START - PHY_START)

#define PHY_EARLY_PGTBL ((unsigned long *)((uint64)early_pgtbl - (uint64)PA2VA_OFFSET))

#define PHY_ADR(va) ((uint64)((uint64)(va) - (uint64)PA2VA_OFFSET))
#define VIS_ADR(pa) ((uint64)((uint64)(pa) + (uint64)PA2VA_OFFSET))

#define NOT_LEAF_PERM ((uint64)0b0000000001)

#endif
