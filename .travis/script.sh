#!/usr/bin/env bash
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
