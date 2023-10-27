#include "printk.h"
#include "sbi.h"
#include "defs.h"
#include "test.h"

int start_kernel()
{
    test(); // DO NOT DELETE !!!

    return 0;
}
