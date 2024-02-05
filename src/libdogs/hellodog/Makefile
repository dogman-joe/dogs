
all: ${BUILD_DIR}/hellodog.o

${BUILD_DIR}/hellodog.o: plat/$(PLAT)/hellodog.c
	$(ARMGNU)-gcc $(COPS) -c ./plat/$(PLAT)/hellodog.c -o ${BUILD_DIR}/hellodog.o
