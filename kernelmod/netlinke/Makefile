MODULE_NAME := netlinke
ifneq ($(KERNELRELEASE),)    
	$(MODULE_NAME)-objs:=$(RESMAN_GLUE_OBJS) $(RESMAN_CORE_OBJS)
	obj-m := netlinke.o
else
	KDIR := /root/poject/sm8250/out

all:
	make -j$(nproc) -C $(KDIR) M=$(shell pwd) LLVM=1 LLVM_IAS=1 ARCH=arm64 CC=clang LD=ld.lld OBJCOPY=llvm-objcopy OBJDUMP=llvm-objdump NM=llvm-nm STRIP=llvm-strip modules -j16
	rm -rf *.o *.mod .*.*.cmd *.mod.o *.mod.c *.symvers *.order .tmp_versions
	llvm-strip --strip-debug $(MODULE_NAME).ko
clean:    
	rm -f *.ko *.o *.mod.o *.mod.c *.symvers    
endif    
