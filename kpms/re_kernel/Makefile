MYKPM_VERSION := 6.0.10
DKF_VERSION := 6.0.10


ifndef KP_DIR
    KP_DIR = ../..
endif

OS_NAME = $(shell uname | tr A-Z a-z)
MACHINE = $(shell uname -m)
ANDROID_NDK_LATEST_HOME := /home/tuzi/PATH/android-ndk-r25c
NDK_BIN_DIR := toolchains/llvm/prebuilt/$(OS_NAME)-$(MACHINE)/bin
ifdef ANDROID_NDK_LATEST_HOME
    NDK_PATH ?= $(ANDROID_NDK_LATEST_HOME)/$(NDK_BIN_DIR)
else ifdef ANDROID_NDK
    NDK_PATH ?= $(ANDROID_NDK)/$(NDK_BIN_DIR)
endif
# ndkr25

ifdef TARGET_COMPILE
    CC := $(TARGET_COMPILE)gcc
    LD := $(TARGET_COMPILE)ld
else ifdef NDK_PATH
    CC := $(NDK_PATH)/aarch64-linux-android31-clang
    LD := $(NDK_PATH)/ld.lld
endif

CFLAGS = -Wall -O2 -fno-PIC -fno-asynchronous-unwind-tables -fno-stack-protector -fno-common -DDKF_VERSION=\"$(DKF_VERSION)$(DKF_VER)\"

INCLUDE_DIRS := . include patch/include linux/include linux/arch/arm64/include linux/tools/arch/arm64/include

INCLUDE_FLAGS := $(foreach dir,$(INCLUDE_DIRS),-I$(KP_DIR)/kernel/$(dir))

objs := re_kernel.o

all: re_kernel_$(DKF_VERSION).kpm

debug: CFLAGS += -DDEBUG
debug: DKF_VER := _d
debug: re_kernel_$(DKF_VERSION)_debug.kpm

re_kernel_$(DKF_VERSION).kpm: ${objs}
	${CC} -r -o $@ $^

re_kernel_$(DKF_VERSION)_debug.kpm: ${objs}
	${CC} -r -o $@ $^

%.o: %.c
	${CC} $(CFLAGS) $(INCLUDE_FLAGS) -c -o $@ $<

.PHONY: clean
clean:
	rm -rf *.kpm
	find . -name "*.o" | xargs rm -f
