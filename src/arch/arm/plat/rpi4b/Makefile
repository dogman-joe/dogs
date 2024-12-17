all: ${BUILD_DIR}/rpi4b_init.o ${BUILD_DIR}/rpi4b_serial.o ${BUILD_DIR}/rpi4b_timer.o ${BUILD_DIR}/rpi4b_intr.o

${BUILD_DIR}/rpi4b_init.o: rpi4b_init.c
	$(ARMGNU)-gcc $(COPS) -c rpi4b_init.c -o ${BUILD_DIR}/rpi4b_init.o
${BUILD_DIR}/rpi4b_serial.o: rpi4b_serial.c
	$(ARMGNU)-gcc $(COPS) -c rpi4b_serial.c -o ${BUILD_DIR}/rpi4b_serial.o
${BUILD_DIR}/rpi4b_timer.o: rpi4b_timer.c
	$(ARMGNU)-gcc $(COPS) -c rpi4b_timer.c -o ${BUILD_DIR}/rpi4b_timer.o
${BUILD_DIR}/rpi4b_intr.o: rpi4b_intr.c
	$(ARMGNU)-gcc $(COPS) -c rpi4b_intr.c -o ${BUILD_DIR}/rpi4b_intr.o

