#! /bin/sh

# Path to the libressl repo
path="../../../libressl-2.9.0"


##### Adding files for aria primitive
# Creating folder for aria primitive
mkdir $path/crypto/aria

# Copy all aria files on openssl
cp ../aria_core.c $path/crypto/aria/aria_core.c
cp ../aria_utils.c $path/crypto/aria/aria_utils.c

cp ../aria_const.h $path/crypto/aria/aria_const.h
cp ../aria_core.h $path/crypto/aria/aria_core.h
cp ../aria_debug.h $path/crypto/aria/aria_debug.h
cp ../aria_test.h $path/crypto/aria/aria_test.h
cp ../aria_type.h $path/crypto/aria/aria_type.h
cp ../aria_utils.h $path/crypto/aria/aria_utils.h
cp aria_locl.h $path/crypto/aria/aria_locl.h

# Modifiyng makefile for aria primitive
cp Makefile.am.crypto $path/crypto/Makefile.am


##### Adding aria.h for openssl using
# Copy aria.h on openssl
cp aria.h $path/include/openssl/aria.h

# Modifiyng makefile for aria.h
cp Makefile.am.include.openssl $path/include/openssl/Makefile.am


