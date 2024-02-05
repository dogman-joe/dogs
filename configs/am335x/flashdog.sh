cat TOC_examples/TOC.bin dog.bin > dogtoc.bin

sudo dd if=dogtoc.bin of=/dev/sda bs=1
sync
rm dogtoc.bin
