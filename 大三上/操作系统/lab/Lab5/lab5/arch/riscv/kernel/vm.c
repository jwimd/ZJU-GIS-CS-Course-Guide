// arch/riscv/kernel/vm.c
#include "defs.h"
#include "printk.h"
#include "types.h"
#include "mm.h"

extern char _stext[];
extern char _etext[];

extern char _srodata[];
extern char _erodata[];

extern char _sdata[];

/* early_pgtbl: 用于 setup_vm 进行 1GB 的 映射。 */
uint64 early_pgtbl[512] __attribute__((__aligned__(0x1000)));
//该声明将强制编译器确保（尽可能）变量类型为structS或者int32_t的变量在分配空间时采用4kb对齐方式。

/* swapper_pg_dir: kernel pagetable 根目录， 在 setup_vm_final 进行映射。 */
uint64 swapper_pg_dir[512] __attribute__((__aligned__(0x1000)));

void setup_vm(void)
{

    /*  将 va 的 64bit 作为如下划分： | high bit | 9 bit | 30 bit |
        high bit 可以忽略
        中间9 bit 作为 early_pgtbl 的 index
        低 30 bit 作为 页内偏移 这里注意到 30 = 9 + 9 + 12， 即我们只使用根页表， 根页表的每个 entry 都对应 1GB 的区域。
    */
    // Page Table Entry 的权限 V | R | W | X 位设置为 1

    //注意：所有符号都被定义在虚拟地址，所以在启动虚拟地址需要反计算到物理地址(unsigned long *)((uint64)early_pgtbl - PA2VA_OFFSET)
    PHY_EARLY_PGTBL[((uint64)PHY_START << 25) >> 55] = (((uint64)PHY_START >> 30) << 28) + 0b0000001111; //等值映射

    PHY_EARLY_PGTBL[((uint64)VM_START << 25) >> 55] = (((uint64)PHY_START >> 30) << 28) + 0b0000001111; //至高映射

    return;
}

void setup_vm_final(void)
{
    memset(swapper_pg_dir, 0x0, PGSIZE);

    // mapping kernel text X|-|R|V
    create_mapping(swapper_pg_dir, (uint64)_stext, PHY_ADR((uint64)_stext), (uint64)_etext - (uint64)_stext, (uint64)VM_TEXT_PERM);

    // mapping kernel rodata -|-|R|V
    create_mapping(swapper_pg_dir, (uint64)_srodata, PHY_ADR((uint64)_srodata), (uint64)_erodata - (uint64)_srodata, (uint64)VM_RODATA_PERM);

    // mapping other memory -|W|R|V
    create_mapping(swapper_pg_dir, (uint64)_sdata, PHY_ADR((uint64)_sdata), (uint64)VM_KERNEL_END - (uint64)_sdata, (uint64)VM_KERNEL_NORMAL_PERM);

    csr_write(satp, (uint64)(0x8000000000000000 + ((uint64)PHY_ADR(swapper_pg_dir) >> 12)));

    // flush TLB
    asm volatile("sfence.vma zero, zero");

    // flush icache
    asm volatile("fence.i");

    return;
}

/* 创建多级页表映射关系 */
void create_mapping(uint64 *pgtbl, uint64 va, uint64 pa, uint64 sz, uint64 perm)
{
    /*
    pgtbl 为根页表的基地址
    va, pa 为需要映射的虚拟地址、物理地址
    sz 为映射的大小
    perm 为映射的读写权限

    创建多级页表的时候使用 kalloc() 来获取一页作为页表目录
    使用 V bit 来判断页表项是否存在
    */
    uint64 offset = 0;

    // 0级页表4kb映射
    for (; offset < sz; offset += PGSIZE)
    {
        uint64 va_offset = va + offset;

        //获取vpn
        uint64 vpn[3] = {
            (va_offset << 43) >> 55,
            (va_offset << 34) >> 55,
            (va_offset << 25) >> 55};

        uint64 *pg_dir_l1, *pg_dir_l0;

        uint64 not_leaf_perm = VM_NOT_LEAF_PERM_KERNEL;
        if ((perm >> 4) == 1)
            not_leaf_perm = VM_NOT_LEAF_PERM_USER;

        // 1gb映射
        if (pgtbl[vpn[2]] == 0)
        {
            pg_dir_l1 = (uint64 *)kalloc();
            pgtbl[vpn[2]] = (((uint64)PHY_ADR(pg_dir_l1) >> 12) << 10) + not_leaf_perm;
        }
        else
            pg_dir_l1 = (uint64 *)(VIS_ADR((pgtbl[vpn[2]] >> 10) << 12));

        if (pg_dir_l1[vpn[1]] == 0)
        {
            pg_dir_l0 = (uint64 *)kalloc();
            pg_dir_l1[vpn[1]] = (((uint64)PHY_ADR(pg_dir_l0) >> 12) << 10) + not_leaf_perm;
        }
        else
            pg_dir_l0 = (uint64 *)(VIS_ADR((pg_dir_l1[vpn[1]] >> 10) << 12));

        pg_dir_l0[vpn[0]] = (uint64)((((pa + offset) >> 12) << 10) + perm);
    }

    return;
}