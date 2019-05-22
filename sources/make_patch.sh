#!/bin/bash
####################################################
# Run security audit tests
####################################################

output="aria.patch"
tmp="buf.tmp"
source="./aria"
dest="./libressl-2.9.0"

echo -e "Generate patch file"

for file in $(find $source/* -type f); do
	echo -e $file

	#Get diff between destination and source
	diff -Naur $dest$tmp $source$tmp > $tmp
	
	#Set target to destination file
	echo "+++ $dest${file#./aria}" >>$output

	#Remove two first lines
	tail -n +2 $tmp >> $output
done
