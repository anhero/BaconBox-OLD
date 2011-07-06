#!/bin/bash

cd "$1"
shift

CMAKE=$(which cmake)
if [ "${CMAKE}" == "" ]; then
	echo "CMake is not correctly installed and is necessary to build this project." && exit 1
fi

if [ ! -d build ]; then
	echo "Configure still has not run."
	echo "PRO-TIP: call configure.bat before compile.bat."
	exit 0
fi

cd build
mingw32-make
