all: ${BUILD_DIR}/head.o ${BUILD_DIR}/cpudog.o ${BUILD_DIR}/vbar.o ${BUILD_DIR}/arch.o ${BUILD_DIR}/rpi4b_init.o ${BUILD_DIR}/rpi4b_serial.o ${BUILD_DIR}/rpi4b_timer.o ${BUILD_DIR}/rpi4b_intr.o

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
${BUILD_DIR}/rpi4b_init.o: plat/rpi4b/rpi4b_init.c
	$(ARMGNU)-gcc -I${PLAT_INC_DIR} $(COPS) -c ./plat/rpi4b/rpi4b_init.c -o ${BUILD_DIR}/rpi4b_init.o
${BUILD_DIR}/rpi4b_serial.o: plat/rpi4b/rpi4b_serial.c
	$(ARMGNU)-gcc -I${PLAT_INC_DIR} $(COPS) -c ./plat/rpi4b/rpi4b_serial.c -o ${BUILD_DIR}/rpi4b_serial.o
${BUILD_DIR}/rpi4b_timer.o: plat/rpi4b/rpi4b_timer.c
	$(ARMGNU)-gcc -I${PLAT_INC_DIR} $(COPS) -c ./plat/rpi4b/rpi4b_timer.c -o ${BUILD_DIR}/rpi4b_timer.o
${BUILD_DIR}/rpi4b_intr.o: plat/rpi4b/rpi4b_intr.c
	$(ARMGNU)-gcc -I${PLAT_INC_DIR} $(COPS) -c ./plat/rpi4b/rpi4b_intr.c -o ${BUILD_DIR}/rpi4b_intr.o
