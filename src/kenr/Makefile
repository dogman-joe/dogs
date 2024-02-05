ARCH_INC=arch/$(ARCH)/inc

all: arch_code ${BUILD_DIR}/notmain.o ${BUILD_DIR}/dogproc.o ${BUILD_DIR}/dogclock.o ${BUILD_DIR}/dogint.o

.PHONY arch_code:
	$(MAKE) -C arch/$(ARCH)

${BUILD_DIR}/notmain.o: notmain.c
	$(ARMGNU)-gcc -I$(ARCH_INC) $(COPS) -c ./notmain.c -o ${BUILD_DIR}/notmain.o
${BUILD_DIR}/dogproc.o: dogproc.c
	$(ARMGNU)-gcc -I$(ARCH_INC) $(COPS) -c ./dogproc.c -o ${BUILD_DIR}/dogproc.o
${BUILD_DIR}/dogclock.o: dogclock.c
	$(ARMGNU)-gcc -I$(ARCH_INC) $(COPS) -c ./dogclock.c -o ${BUILD_DIR}/dogclock.o
${BUILD_DIR}/dogint.o: dogint.c
	$(ARMGNU)-gcc -I$(ARCH_INC) $(COPS) -c ./dogint.c -o ${BUILD_DIR}/dogint.o
