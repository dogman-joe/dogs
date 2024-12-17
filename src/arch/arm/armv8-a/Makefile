all: ${BUILD_DIR}/head.o ${BUILD_DIR}/cpudog.o ${BUILD_DIR}/vbar.o ${BUILD_DIR}/arch.o 

ARCH_INC_DIR=inc
PLAT_INC_DIR=plat/inc

${BUILD_DIR}/head.o: head.s
	$(ARMGNU)-gcc $(COPS) -c ./head.s -o ${BUILD_DIR}/head.o
${BUILD_DIR}/vbar.o: vbar.s
	$(ARMGNU)-gcc $(COPS) -c ./vbar.s -o ${BUILD_DIR}/vbar.o
${BUILD_DIR}/cpudog.o: cpudog.s
	$(ARMGNU)-gcc $(COPS) -c ./cpudog.s -o ${BUILD_DIR}/cpudog.o
${BUILD_DIR}/arch.o: arch.c
	$(ARMGNU)-gcc -I${ARCH_INC_DIR} $(COPS) -c ./arch.c -o ${BUILD_DIR}/arch.o
