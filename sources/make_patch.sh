#!/bin/bash
#***********************************************************************
# FILENAME :        make_patch.sh
#
# DESCRIPTION :
#       List all files inside source (aria) directory to perform a diff
#       base on dest (libressl) directory.
#       All differents are reported inside output file
#
#
# NOTES :
#        Install patch command: patch -p0 < aria.patch
#        Launch command inside sources directory
#
#
#
# AUTHOR :    Allard Chris & Aulagnier Corentin
# START DATE :  02-2019
#
# Version : 0.1
#
#
#**********************************************************************

# Output name for patch file
output="aria.patch"

# Buffer file for process.
tmp="buf.tmp"

# Source of our new/modified files
source="./aria"

# Destination to copy
dest="./libressl-2.9.0"

echo -e "Generate patch file"

rm $output 2> /dev/null

for file in $(find $source/* -type f); do
	echo -e $file

	#Get diff between destination and source
	diff -Naur $dest${file#./aria} $source${file#./aria} > $tmp

	#Set target to destination file
	echo "+++ $dest${file#./aria}" >>$output

	#Remove two first lines
	tail -n +3 $tmp >> $output
done

rm $tmp 2> /dev/null
