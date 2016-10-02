#!/bin/bash

set -e
if [ -d "build" ]; then
	rm -fr build
fi

mkdir build
cd build

cmake ..
make
./runtests


cd ..
