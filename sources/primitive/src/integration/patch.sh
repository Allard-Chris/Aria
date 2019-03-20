#! /bin/sh

# Important Path for patching
libressl_path="../../../libressl-2.9.0"


#################################################
##### libressl/app/openssl
cp ./app/openssl/openssl.c $libressl_path/app/openssl/openssl.c
cp ./app/openssl/genrsa.c $libressl_path/app/openssl/genrsa.c
cp ./app/openssl/gendsa.c $libressl_path/app/openssl/gendsa.c
cp ./app/openssl/smime.c $libressl_path/app/openssl/smime.c
cp ./app/openssl/pkcs12.c $libressl_path/app/openssl/pkcs12.c
cp ./app/openssl/speed.c $libressl_path/app/openssl/speed.c


#################################################
##### libressl/crypto
# Creating folder for aria primitive
mkdir $libressl_path/crypto/aria

# Copy all aria files on crypto/aria
cp ./crypto/aria/aria_core.c $libressl_path/crypto/aria/aria_core.c
cp ./crypto/aria/aria_locl.h $libressl_path/crypto/aria/aria_locl.h

# Modifiyng makefiles and other files
cp ./crypto/Makefile.am $libressl_path/crypto/Makefile.am
cp ./crypto/objects/obj_dat.h $libressl_path/crypto/objects/obj_dat.h # no modifications for now
cp ./crypto/CMakefile.txt $libressl_path/crypto/CMakefile.txt
cp ./crypto/Makefile.in $libressl_path/crypto/Makefile.in


#################################################
##### libressl/include/openssl
cp ./include/openssl/aria.h $libressl_path/include/openssl/aria.h

# Modifiyng makefiles and other files
cp ./include/openssl/Makefile.am $libressl_path/include/openssl/Makefile.am
cp ./include/openssl/obj_mac.h $libressl_path/include/openssl/obj_mac.h
cp ./include/openssl/Makefile.in $libressl_path/include/openssl/Makefile.in
