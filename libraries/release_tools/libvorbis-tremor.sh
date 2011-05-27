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
#	pushd Tremor
	patch <<EOF
Index: configure.in
===================================================================
--- configure.in	(révision 17981)
+++ configure.in	(copie de travail)
@@ -11,7 +11,7 @@
 
 AM_CONFIG_HEADER([config.h])
 
-AM_INIT_AUTOMAKE(libvorbisidec,1.2.0)
+AM_INIT_AUTOMAKE(libvorbisidec,1.2.x-rb17981)
 
 dnl AM_MAINTAINER_MODE only provides the option to configure to enable it
 AM_MAINTAINER_MODE
@@ -152,4 +152,4 @@
 AC_SUBST(DEBUG)
 AC_SUBST(PROFILE)
 
-AC_OUTPUT(Makefile Version_script vorbisidec.pc)
+AC_OUTPUT(Makefile vorbisidec.pc)
EOF
#	popd
}
function patching2() {
	echo "Patching configure..."
	patch -N <<'EOF'
--- configure	2011-05-13 14:19:56.040817075 -0400
+++ configure	2011-05-13 14:30:56.456451003 -0400
@@ -11503,18 +11503,6 @@
 
 
 
-if test "x$lt_cv_prog_gnu_ld" = "xyes"; then
-   SHLIB_VERSION_ARG="Wl,--version-script=Version_script"
-
-      case "$target_os" in
-  linux* | solaris* )
-    SHLIB_VERSION_ARG="-Wl,--version-script=Version_script"
-    ;;
-  *)
-    ;;
-   esac
-   LDFLAGS="$LDFLAGS $SHLIB_VERSION_ARG"
-fi
 
 
 # Check whether --enable-low-accuracy was given.
EOF
	if [ $? -gt 0 ]; then
		echo "NO WAY, patch didn't work?"
		exit 1
	fi
}
function make_release() {
	echo Making release
	pushd Tremor

	rm 'Version_script.in'
	patching

	./autogen.sh

	patching2
	
	
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
make_release
