
export ARMGNU ?= arm-none-eabi
#ARMGNU ?= arm-linux-gnueabi
INC_DIR=${CURDIR}/inc

export AOPS = --warn --fatal-warnings
export COPS = -I${INC_DIR} -Wall -Werror -nostdlib -nostartfiles -ffreestanding -mcpu=cortex-a8

export SRC_DIR=${CURDIR}/src
export BUILD_DIR=${CURDIR}/build


all : clean src_code dog.bin

clean :
	rm -f ${BUILD_DIR}/*

.PHONY src_code:
	$(MAKE) -C src


OFILES=$(wildcard ${BUILD_DIR}/*.o)

${BUILD_DIR}/notmain.elf : AMC355x_memmap ${OBJFILES}
	echo ${OFILES}
	$(ARMGNU)-ld ${OFILES} -T AMC355x_memmap -o ${BUILD_DIR}/notmain.elf
	$(ARMGNU)-objdump -D ${BUILD_DIR}/notmain.elf > notmain.list

dog.bin : ${BUILD_DIR}/notmain.elf
	$(ARMGNU)-objcopy ${BUILD_DIR}/notmain.elf -O binary notmain.bin
	cat TOC_examples/TOC.bin notmain.bin > dog.bin
	cat notmain.bin > kernel8.img
#	cat notmain.bin > dog.bin
	rm notmain.bin

