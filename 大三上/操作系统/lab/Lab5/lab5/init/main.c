#include "printk.h"
#include "sbi.h"
#include "defs.h"
#include "test.h"
#include "proc.h"

int start_kernel()
{
    schedule();
    test(); // DO NOT DELETE !!!

    return 0;
}
