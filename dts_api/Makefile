obj-m += dts_api.o

CROSS_COMPILE=arm-linux-gnueabihf-
ARCH=arm
#KERNEL_PATH=/home/vmuser/workspace/am335x/am335x-linux4.4.41/am335x
KERNEL_PATH=/home/luyingjian/data/6580_code/ZYNQ7010/zynq_buildroot_sdk/out/kernel

all:
	make -C $(KERNEL_PATH) M=$(shell pwd) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) modules

clean:
	rm .*  *mod.c *.symvers *.order *.ko *.o* 
	rm -r .tmp_versions
#	make -C $(KERNEL_PATH) COMPILE_CORESS=$(GCC)
