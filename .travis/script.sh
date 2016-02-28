#!/usr/bin/env bash
echo $SPECIFIC_CMAKE

cmake --version
make --version
if [ -d build ]; then
    rm -rf build
fi
mkdir build
cd build

if [! -z "$var" ]; then
    (${SPECIFIC_CMAKE} ..)
else
    cmake ..
fi

make
./../bin/runTests
