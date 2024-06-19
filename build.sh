#!/bin/bash

mkdir -p build
cd build

cmake -G "MinGW Makefiles" ..

mingw32-make -j`nproc`