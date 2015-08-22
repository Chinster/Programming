obj-m += random-dev.o

KERNEL_DIR=/lib/modules/`uname -r`/build

all:
	make -C ${KERNEL_DIR} M=$(PWD) modules
clean:
	make -C ${KERNEL_DIR} M=$(PWD) clean
