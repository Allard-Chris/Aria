#!/bin/bash
####################################################
# Run security audit tests
####################################################

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
