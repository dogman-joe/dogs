all: ${BUILD_DIR}/head.o ${BUILD_DIR}/arch.o ${BUILD_DIR}/am335x_init.o ${BUILD_DIR}/am335x_intr.o ${BUILD_DIR}/am335x_timer.o  ${BUILD_DIR}/vbar.o

ARCH_INC_DIR=inc
PLAT_INC_DIR=plat/inc

${BUILD_DIR}/head.o: head.s
	$(ARMGNU)-gcc $(COPS) -c ./head.s -o ${BUILD_DIR}/head.o
${BUILD_DIR}/arch.o: arch.c
	$(ARMGNU)-gcc -I${ARCH_INC_DIR} $(COPS) -c ./arch.c -o ${BUILD_DIR}/arch.o
${BUILD_DIR}/vbar.o: vbar.s
	$(ARMGNU)-gcc $(COPS) -c ./vbar.s -o ${BUILD_DIR}/vbar.o
${BUILD_DIR}/am335x_init.o: plat/am335x/am335x_init.c
	$(ARMGNU)-gcc -I${PLAT_INC_DIR} $(COPS) -c ./plat/am335x/am335x_init.c -o ${BUILD_DIR}/am335x_init.o
${BUILD_DIR}/am335x_intr.o: plat/am335x/am335x_intr.c
	$(ARMGNU)-gcc -I${PLAT_INC_DIR} $(COPS) -c ./plat/am335x/am335x_intr.c -o ${BUILD_DIR}/am335x_intr.o
${BUILD_DIR}/am335x_timer.o: plat/am335x/am335x_timer.c
	$(ARMGNU)-gcc -I${PLAT_INC_DIR} $(COPS) -c ./plat/am335x/am335x_timer.c -o ${BUILD_DIR}/am335x_timer.o
${BUILD_DIR}/am335x_gpio.o: plat/am335x/am335x_gpio.c
	$(ARMGNU)-gcc -I${PLAT_INC_DIR} $(COPS) -c ./plat/am335x/am335x_gpio.c -o ${BUILD_DIR}/am335x_gpio.o
