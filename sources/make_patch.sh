#!/bin/bash
####################################################
# Run security audit tests
####################################################

output="aria.patch"
source="./aria"
dest="./libressl-2.9.0"

echo -e "Generate patch file"

for file in $(find $source/* -type f); do
	tmp=${file#./aria}
	echo "+++ $dest$tmp" >>$output
	diff -Nuar $dest$tmp $source$tmp >> $output
done
