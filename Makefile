include .config

INC_DIR=${CURDIR}/inc

export SRC_DIR=${CURDIR}/src
export BUILD_DIR=${CURDIR}/build


all : clean src_code dog.bin

clean :
	rm -f ${BUILD_DIR}/*
distclean:
	rm .config
	rm memmap
	rm flashdog.sh

.PHONY src_code:
	$(MAKE) -C src

OFILES=$(wildcard ${BUILD_DIR}/*.o)

${BUILD_DIR}/notmain.elf : memmap ${OBJFILES}
	echo ${OFILES}
	$(ARMGNU)-ld ${OFILES} -T memmap -o ${BUILD_DIR}/notmain.elf
	$(ARMGNU)-objdump -D ${BUILD_DIR}/notmain.elf > notmain.list

dog.bin : ${BUILD_DIR}/notmain.elf
	$(ARMGNU)-objcopy ${BUILD_DIR}/notmain.elf -O binary dog.bin
	cat dog.bin > kernel8.img

