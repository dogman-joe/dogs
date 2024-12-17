all: ${BUILD_DIR}/am335x_init.o ${BUILD_DIR}/am335x_timer.o ${BUILD_DIR}/am335x_intr.o

${BUILD_DIR}/am335x_init.o: am335x_init.c
	$(ARMGNU)-gcc $(COPS) -c am335x_init.c -o ${BUILD_DIR}/am335x_init.o
${BUILD_DIR}/am335x_timer.o: am335x_timer.c
	$(ARMGNU)-gcc $(COPS) -c am335x_timer.c -o ${BUILD_DIR}/am335x_timer.o
${BUILD_DIR}/am335x_intr.o: am335x_intr.c
	$(ARMGNU)-gcc $(COPS) -c am335x_intr.c -o ${BUILD_DIR}/am335x_intr.o

