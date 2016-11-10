#!/usr/bin/env bash
cmake --version
make --version
if [ -d build ]; then
    rm -rf build
fi
if [ -d bin ]; then
    rm -rf bin
fi
mkdir build
mkdir bin
echo "This directory contains all the output binary files." > bin/README.md
cd build
if [ -f /home/luker/Applications/clion-1.2.4/bin/cmake/bin/cmake ]; then
    /home/luker/Applications/clion-1.2.4/bin/cmake/bin/cmake ..
else
    cmake ..
fi
make
./../bin/runTests
