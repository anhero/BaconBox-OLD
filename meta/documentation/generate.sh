#!/bin/bash -ue

# This script is for maintainer uses. It may have non-portable features.
# If you need to change something to make it work on your platform, please
# send us a patch, we'll take it in consideration.

# By the way, this is a quick and dirty script ;)

export script_dir="$(dirname "${BASH_SOURCE[0]}")"
declare -r script_dir

function print_help() {
	local this="${0}"
	cat <<END_OF_HELP
Usage:
	$this [version]

This script is used to generate the documentation.
This is an helper to allow parameters for other 
documentation generation (LaTeX, CHM, QHP).

END_OF_HELP
}

#TODO: Better parameters parsing...
if [[ $# -gt 0 ]]; then
	if [ $# -gt 1 -o "$1" == "--help" -o "$1" == "-h" ]; then
		print_help
		exit 0
	fi
	version="$1"
	print_version="$1"
else
	version="stable"
fi

##############################################
# Version finding...

HG=${HG-hg}
declare -r HG

# Checking if mercurial is available
if ! which $HG > /dev/null; then
	echo 'Mercurial is not available as `'$HG'`.' >&2;
	exit 1
fi

# Special case for the tag stable
if [[ $version == "stable" ]]; then
	print_version=$(hg parent -R "${script_dir}/../../" --template "{latesttag}-dev+{latesttagdistance}\n")
	print_version=${print_version#"stable:"}
	print_version=${print_version#"v"}
fi

if [[ $print_version =~ v[[:digit:]].* ]]; then
	print_version=${print_version#v}
fi

echo Generating doc for \"$print_version\";

cd $script_dir;

OPTIONS=""
OPTIONS=`echo "PROJECT_NUMBER=\"${print_version}\""`

( cat Doxyfile ; echo "$OPTIONS" ) | doxygen -

echo -e '\n\n\n'
echo "...Done!"

