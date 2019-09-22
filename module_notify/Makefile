obj-m += buildchain.o
obj-m += regchain.o
obj-m += notify.o

GCC=arm-linux-gnueabihf-
ARCH=arm
KERNEL_PATH=/home/vmuser/workspace/am335x/am335x-linux4.4.41/am335x

all:
	make -C $(KERNEL_PATH) M=$(shell pwd) ARCH=$(ARCH) CROSS_COMPILE=$(GCC) modules

clean:
	rm  *.symvers *.order *.ko *.o *.mod*
#	make -C $(KERNEL_PATH) COMPILE_CORESS=$(GCC)