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
	$this [options] [version]

The version can be any string, but if it is not given
or "stable", the version will be calculated using mercurial.

OPTIONS
	--clean             Will remove generated files beforehand
	--generate-qhp      Will generate the QHP files for Qt Creator
	--generate-latex    Will generate the latex files
	--generate-chm      Will generate the compiled HTML Help file
	--without-html      Will not generate HTML files.

This script is used to generate the documentation.
This is an helper to allow parameters for other 
documentation generation (LaTeX, CHM, QHP).

END_OF_HELP
}

###########################################################
# {{{ Parameters parsing

# Default values

OPTIONS=""
version="stable"
print_version="$version"
opt_clean="false"

#Keep a save of the parameters
FULL_PARAMETERS="$@"

while [ $# -gt 0 ];do
	case "$1" in
		--help|-h|'-?'|'/?')
			print_help
			exit 0
			;;
		--generate-qhp)
			OPTIONS=( ${OPTIONS[@]} 'GENERATE_QHP="YES"' )
			;;
		--generate-latex)
			OPTIONS=( ${OPTIONS[@]} 'GENERATE_LATEX="YES"' )
			;;
		--generate-chm)
			OPTIONS=( ${OPTIONS[@]} 'GENERATE_HTMLHELP="YES"' )
			;;
		--without-html)
			OPTIONS=( ${OPTIONS[@]} 'GENERATE_HTML="NO"' )
			;;
		--clean)
			opt_clean="true"
			;;
		# If all else fails.
		*)
			version="$1"
			print_version="$1"
			;;
	esac
	shift;
done

# }}}

###########################################################
# {{{ Version finding...

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

# }}}

###########################################################
# Actual work

# Add the project version to the options
OPTIONS=( ${OPTIONS[@]} 'PROJECT_NUMBER="'${print_version}'"')

cd $script_dir;

echo "Cleaning previously generated files."
if [[ $opt_clean == "true" ]] ; then
	rm -rf generated
fi

echo "OPTIONS:"
for o in "${OPTIONS[@]}"; do
	echo "--> " $o
done
echo "..."

echo Generating doc for \"$print_version\";


( cat Doxyfile ; for o in "${OPTIONS[@]}"; do echo "$o"; done ) | doxygen -

echo -e '\n\n\n'
echo "...Done!"

