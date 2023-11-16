all: arch_code ${BUILD_DIR}/notmain.o ${BUILD_DIR}/dogproc.o ${BUILD_DIR}/dogclock.o ${BUILD_DIR}/dogint.o

.PHONY arch_code:
	$(MAKE) -C arch/armv7-a

${BUILD_DIR}/notmain.o: notmain.c
	$(ARMGNU)-gcc $(COPS) -c ./notmain.c -o ${BUILD_DIR}/notmain.o
${BUILD_DIR}/dogproc.o: dogproc.c
	$(ARMGNU)-gcc $(COPS) -c ./dogproc.c -o ${BUILD_DIR}/dogproc.o
${BUILD_DIR}/dogclock.o: dogclock.c
	$(ARMGNU)-gcc $(COPS) -c ./dogclock.c -o ${BUILD_DIR}/dogclock.o
${BUILD_DIR}/dogint.o: dogint.c
	$(ARMGNU)-gcc $(COPS) -c ./dogint.c -o ${BUILD_DIR}/dogint.o
