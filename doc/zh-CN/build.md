# 构建

## 构建 kpimg

需要交叉编译链
[在此处下载](https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads)

```shell
export TARGET_COMPILE=aarch64-none-elf-
cd kernel
export ANDROID=1 
make
```

## 构建 kptools


- 使用 Makefile

```shell
export ANDROID=1
cd tools
make
```

- 使用 CMake

```shell
cd tools
mkdir build
cd build
cmake ..
make
```

## 构建 kpatch

kpatch在目标系统中运行，如果你在android中使用
可以用 AndroidKernelPatch。

- 使用 Makefile

```shell
cd user
make
```

- 使用 CMake

```shell
cd user
mkdir build
cd build
cmake ..
make
```

- 为 Android 编译

```shell
export ANDROID_NDK=/path/to/ndk
export ANDROID=1
cd user
mkdir -p build/android && cd build/android
cmake -DCMAKE_TOOLCHAIN_FILE=$ANDROID_NDK/build/cmake/android.toolchain.cmake \
-DCMAKE_BUILD_TYPE=Release \
-DANDROID_PLATFORM=android-33 \
-DANDROID_ABI=arm64-v8a ../..
cmake --build .
```

## 构建 KernelPatch 模块

示例：

```shell
export TARGET_COMPILE=aarch64-none-elf-
cd kpm-demo/hello
make
```
