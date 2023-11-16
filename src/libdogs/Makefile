all: ${BUILD_DIR}/dogpio.o

.PHONY arch_code:
	$(MAKE) -C arch/armv7-a

${BUILD_DIR}/dogpio.o: dogpio/dogpio.c
	$(ARMGNU)-gcc $(COPS) -c ./dogpio/dogpio.c -o ${BUILD_DIR}/dogpio.o
