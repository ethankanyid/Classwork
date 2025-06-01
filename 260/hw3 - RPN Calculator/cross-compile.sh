#!/bin/bash
SDK_DIR="$1"
source $PWD/${SDK_DIR}
make clean; make -j$(nproc) "CFLAGS=$CFLAGS" "LDFLAGS=$LDFLAGS" "CC=$CC" "CXX=$CXX" "AS=$AS" "ASFLAGS=$ASFLAGS"

