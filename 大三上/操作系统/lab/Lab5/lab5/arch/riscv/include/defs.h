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

#define USER_START (0x0000000000000000) // user space start virtual address
#define USER_END (0x0000004000000000)   // user space end virtual address

#define VM_TEXT_PERM 0b0000001011
#define VM_RODATA_PERM 0b0000000011
#define VM_KERNEL_NORMAL_PERM 0b0000000111

#define VM_USER_PERM_R_W_X 0b0000011111
#define VM_USER_PERM_R_W 0b0000010111
#define VM_USER_PERM_R_X 0b0000011011
#define VM_USER_PERM_R 0b0000010011

#define VM_NOT_LEAF_PERM_KERNEL ((uint64)0b0000000001)
#define VM_NOT_LEAF_PERM_USER ((uint64)0b0000010001)

#endif
