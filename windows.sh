#!/bin/sh

mkdir build
cd build
cmake -G "Visual Studio 15 Win64" -DCMAKE_BUILD_TYPE=Debug ..
