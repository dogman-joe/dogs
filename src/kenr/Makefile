ARCH_INC=../arch/arm/$(ARCH)/inc

all: ${BUILD_DIR}/dogmain.o ${BUILD_DIR}/dogproc.o ${BUILD_DIR}/dogclock.o ${BUILD_DIR}/dogint.o

${BUILD_DIR}/dogmain.o: dogmain.c
	$(ARMGNU)-gcc -I$(ARCH_INC) $(COPS) -c ./dogmain.c -o ${BUILD_DIR}/dogmain.o
${BUILD_DIR}/dogproc.o: dogproc.c
	$(ARMGNU)-gcc -I$(ARCH_INC) $(COPS) -c ./dogproc.c -o ${BUILD_DIR}/dogproc.o
${BUILD_DIR}/dogclock.o: dogclock.c
	$(ARMGNU)-gcc -I$(ARCH_INC) $(COPS) -c ./dogclock.c -o ${BUILD_DIR}/dogclock.o
${BUILD_DIR}/dogint.o: dogint.c
	$(ARMGNU)-gcc -I$(ARCH_INC) $(COPS) -c ./dogint.c -o ${BUILD_DIR}/dogint.o
