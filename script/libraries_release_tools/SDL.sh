#!/bin/bash -ue
this_dir="$(dirname "$0")"

_hg_rev="50bf98210aae"
_hg_url="http://hg.libsdl.org/SDL/"
_name="SDL"

function fetch() {
	echo Fetching sources
	hg clone "${_hg_url}" ${_name} || hg pull -R "${_name}"
	hg -R "${_name}" update -C --rev ${_hg_rev}
	#Clean-up everything
	pushd "${_name}"
	hg update -C null
	rm -rf *
	popd
	hg -R "${_name}" update -C --rev ${_hg_rev}
}
function make_release() {
	echo Making release
	pushd ${_name}

	./autogen.sh
	./configure
	sed -i 'Makefile' -e 's/distdir = SDL-1.3.0/distdir = SDL-1.3.0-'${_hg_rev}'/'
	make dist

	popd

	mv ${_name}/${_name}-1.3.0-${_hg_rev}.tar.gz ../
}
function init() {
cd "$this_dir"
mkdir -p "$_name"
cd "$_name"
}

init
fetch
make_release
