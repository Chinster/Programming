obj-m += hello.o
obj-m += coding_style.o

KERNEL_DIR=/lib/modules/`uname -r`/build

all:
	make -C ${KERNEL_DIR} M=$(PWD) modules
clean:
	make -C ${KERNEL_DIR} M=$(PWD) clean
