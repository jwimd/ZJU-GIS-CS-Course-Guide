#include "types.h"
#include "sbi.h"

struct sbiret sbi_ecall(int ext, int fid, uint64 arg0,
						uint64 arg1, uint64 arg2,
						uint64 arg3, uint64 arg4,
						uint64 arg5)
{
	register unsigned int a0 = 0, a1 = 0;
	__asm__ volatile(
		"mv a7, %[ext]\n"
		"mv a6, %[fid]\n"
		"mv a0, %[arg0]\n"
		"mv a1, %[arg1]\n"
		"mv a2, %[arg2]\n"
		"mv a3, %[arg3]\n"
		"mv a4, %[arg4]\n"
		"mv a5, %[arg5]\n"

		:

		: [ext] "r"(ext),
		  [fid] "r"(fid),
		  [arg0] "r"(arg0),
		  [arg1] "r"(arg1),
		  [arg2] "r"(arg2),
		  [arg3] "r"(arg3),
		  [arg4] "r"(arg4),
		  [arg5] "r"(arg5)

		: "memory");
	//将变量值写入寄存器
	__asm__ volatile(
		"ecall" //调用ecall指令

		: [a0] "=r"(a0), [a1] "=r"(a1) //结果写入变量

		:

		: "memory");

	struct sbiret return_value;
	return_value.error = a0;
	return_value.value = a1;

	return return_value;
}
