#!/bin/bash
this="$(dirname "$0")"

# _svn_rev="17374" #Last release with bundled ogg

_svn_rev="17981"
_svn_url="http://svn.xiph.org/trunk/Tremor/"
_name="libvorbisidec"

function fetch() {
	echo Fetching sources
	svn co "${_svn_url}@${_svn_rev}"
	pushd Tremor
	svn revert -R .
	popd
}
function patching() {
	echo Patching
	pushd Tremor
	patch <<EOF
Index: configure.in
===================================================================
--- configure.in	(révision 17374)
+++ configure.in	(copie de travail)
@@ -11,7 +11,7 @@
 
 AM_CONFIG_HEADER([config.h])
 
-AM_INIT_AUTOMAKE(libvorbisidec,1.2.0)
+AM_INIT_AUTOMAKE(libvorbisidec,1.2.x-rb${_svn_rev})
 
 dnl AM_MAINTAINER_MODE only provides the option to configure to enable it
 AM_MAINTAINER_MODE
EOF
	popd
}
function make_release() {
	echo Making release
	pushd Tremor
	./autogen.sh
	make dist-bzip2
	popd
	mv Tremor/libvorbisidec-1.2.x-rb${_svn_rev}.tar.bz2 ../
}
function init() {
cd "$this"
mkdir -p "$_name"
cd "$_name"
}

init
fetch
patching
make_release
