CROSS_COMPILE = riscv64-linux-gnu-
CFLAGS = -nostdlib -fno-builtin -march=rv32ima -mabi=ilp32 -g -Wall

CC = ${CROSS_COMPILE}gcc
OBJDUMP = ${CROSS_COMPILE}objdump
READELF = ${CROSS_COMPILE}readelf

QEMU = qemu-system-riscv32
QFLAGS = -nographic -smp 1 -machine virt -bios none

EXEC = test
SRC = ${EXEC}.s

.DEFAULT_GOAL := all
all:
	@${CC} ${CFLAGS} ${SRC} -Ttext=0x80200000 -o ${EXEC}.elf

.PHONY : objdump
objdump: all
	@${OBJDUMP} -S ${EXEC}.elf

.PHONY : run
run: all
	@${QEMU} ${QFLAGS} -kernel ./${EXEC}.elf

.PHONY : readelf
readelf: all
	@${READELF} -S ${EXEC}.elf

.PHONY : map
map: all
	nm ${EXEC}.elf

.PHONY : clean
clean:
	rm -rf *.o *.elf