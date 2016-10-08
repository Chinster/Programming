#obj-m += chardev.o
#obj-m += hello_proc.o
#obj-m += steal_syscall.o
obj-m += keylog.o

KERNEL_DIR=/lib/modules/`uname -r`/build

all:
	make -C ${KERNEL_DIR} M=$(PWD) modules
clean:
	make -C ${KERNEL_DIR} M=$(PWD) clean
