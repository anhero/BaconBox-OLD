#!/bin/bash

# This script calls cmake properly for the MinGW environment

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

if [ -d build ]; then
	echo "Configure already ran."
	echo "PRO-TIP: Delete the build directory to re-configure."
	exit 0
fi

#######################################
# Stripping MSYS from path for cmake...
ORIGPATH="$PATH"
ORIGIFS="$IFS"
IFS=":"
for p in $PATH; do
	if [[ -n "$NEWPATH" ]]; then
		NEWPATH="$NEWPATH:"
	fi
	if [[ "$p" == '/usr/bin' ]]; then
		echo "Stripping MSYS from path"
	elif [[ "$p" == '/bin' ]]; then
		echo "Stripping MSYS from path"
	else
		NEWPATH="$NEWPATH$p"
	fi
done
IFS="$ORIGIFS"
#######################################

mkdir -p build
cd build


OPENALDIR="/c/Program Files/OpenAL 1.1 SDK/"

export _BASH_INTERPRETER=$(which bash)

PATH="$NEWPATH"
cmake -DSDL=1 -G"MinGW Makefiles" ..
PATH="$ORIGPATH"
