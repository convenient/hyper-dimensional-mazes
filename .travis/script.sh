#!/usr/bin/env bash
echo $PATH
which cmake
cmake --version
make --version
if [ -d build ]; then
    rm -rf build
fi
mkdir build
cd build
cmake ..
make
./../bin/runTests
