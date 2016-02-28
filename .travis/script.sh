#!/usr/bin/env bash
echo $SPECIFIC_CMAKE
which cmake
cmake --version
make --version
if [ -d build ]; then
    rm -rf build
fi
mkdir build
cd build

if [ ! -z "${SPECIFIC_CMAKE}" ]; then
    (${SPECIFIC_CMAKE} ..)
else
    cmake ..
fi

make
./../bin/runTests
