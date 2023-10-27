#include "print.h"
#include "sbi.h"
#include "defs.h"

extern void test();

int start_kernel()
{

    puti(2022);
    puts(" Hello RISC-V\n");

    test(); // DO NOT DELETE !!!

    return 0;
}
