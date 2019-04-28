#! /bin/sh
# This bash will create the patch file for libressl-aria inside libressl

diff -Naur ./libressl-2.9.0 ./libressl-2.9.0-aria > aria.patch
