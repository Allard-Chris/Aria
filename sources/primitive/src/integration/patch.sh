#! /bin/sh


cd libressl-2.9.0

# Creating file for aria primitive
mkdir crypto/aria

# Copy aria.h on openssl
cp .../aria.c crypto/aria/aria.c

# Copy aria.h on openssl
cp .../aria.h include/openssl/aria.h

# Copy aria.h on openssl
cp .../build.info .../build.info

