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
	diff -Nu $dest$tmp $source$tmp >> $output
done
