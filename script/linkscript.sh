#!/bin/bash

# linkscript.sh [--verbose] outputfile input [input[...]]


verbose="false"
if [ "$1" == "--verbose" ]; then
	shift
	verbose="true"
fi


function dir_resolve() {
	cd "$1" 2>/dev/null || return $?
	echo "$(pwd -P)"
}

function vecho() {
	if [ "$verbose" == "true" ]; then
		echo $*
	fi
}

outfile=$1
shift

echo "-----------------------"
echo "Building static big lib"
echo "-----------------------"
echo "--> $(basename ${outfile})"

outdir=$(dirname "${outfile}")

vecho » mkdir -p "${outdir}"
mkdir -p "${outdir}"
outdir=$(dir_resolve "${outdir}")
outfile="${outdir}/$(basename ${outfile})"
tempdir="${outdir}/tmp"

vecho » mkdir -p "${tempdir}"
mkdir -p "${tempdir}"

vecho Looping on libraries
for lib in "${@}"; do
	origdir="$PWD"
	vecho "	${lib}"
	libdir="$(dirname ${lib})"
	libdir=$(dir_resolve "${libdir}")
	ar x "$lib"
	mv *.o "${tempdir}/"
	cd "${origdir}"
done;

vecho "Archiving it all together"

vecho » cd ${tempdir}
cd ${tempdir}

vecho » ar rcs "${outfile}" *.o
if ! ar rcs "${outfile}" *.o; then
	echo "An error happened...";
	exit 1;
fi

vecho "Removing temp directory"

cd ${outdir}
rm -rf ${tempdir}
