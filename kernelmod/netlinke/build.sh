#!/bin/bash
export TOOL_PATH=/home/tuzi/PATH/proton-clang
export PATH=${TOOL_PATH}/bin:$PATH
export TOOL_PATH=/home/tuzi/PATH/aarch64-linux-android-4.9
export PATH=${TOOL_PATH}/bin:$PATH
export TOOL_PATH=/home/tuzi/PATH/arm-linux-androideabi-4.9
export PATH=${TOOL_PATH}/bin:$PATH

export CLANG_TRIPLE=aarch64-linux-gnu-
export CROSS_COMPILE_COMPAT=arm-linux-gnueabi-
export CROSS_COMPILE=aarch64-linux-gnu-
export CROSS_COMPILE_ARM32=arm-linux-androideabi-

make
