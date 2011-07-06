#!/bin/bash

cd "$1"
shift

CMAKE=$(which cmake)
if [ "${CMAKE}" == "" ]; then
	echo "CMake is not correctly installed and is necessary to build this project." && exit 1
fi

LIBBUILDTOOL=$(which libbuildtool)
if [ "${LIBBUILDTOOL}" == "" ]; then
	echo "libbuildtool is not correctly installed and is necessary to build the dependencies of this project." && exit 1
fi

if [ ! -d build ]; then
	echo "Configure still has not run."
	echo "PRO-TIP: call configure.bat before compile.bat."
	exit 0
fi


if [ ! -d libraries/current ]; then
	echo "Libbuildtool wasn't called; calling it."
	ORIGDIR="$(pwd)"
	cd libraries
	libbuildtool || ( echo Problem with libbuildtool, bailing out. ; exit 1)
	cp -prf "$(uname -s)/$(uname -m)" current
	echo "Back to $ORIGDIR"
	cd "$ORIGDIR"
fi


cd build
mingw32-make
