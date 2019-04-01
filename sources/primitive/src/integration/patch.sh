#! /bin/sh

# Important Path for patching
libressl_path=. #"../../../libressl-2.9.0"
script_path="$( cd "$(dirname "$0")" ; pwd -P )"

#################################################
##### libressl/app/openssl
cp $script_path/apps/openssl/openssl.c $libressl_path/apps/openssl/openssl.c
cp $script_path/apps/openssl/genrsa.c $libressl_path/apps/openssl/genrsa.c
cp $script_path/apps/openssl/gendsa.c $libressl_path/apps/openssl/gendsa.c
cp $script_path/apps/openssl/smime.c $libressl_path/apps/openssl/smime.c
cp $script_path/apps/openssl/pkcs12.c $libressl_path/apps/openssl/pkcs12.c
cp $script_path/apps/openssl/speed.c $libressl_path/apps/openssl/speed.c


#################################################
##### libressl/crypto
# Creating folder for aria primitive
mkdir $libressl_path/crypto/aria

# Copy all aria files on crypto/aria
cp $script_path/crypto/aria/aria_core.c $libressl_path/crypto/aria/aria_core.c
cp $script_path/crypto/aria/aria_locl.h $libressl_path/crypto/aria/aria_locl.h

# Modifiyng makefiles and other files
cp $script_path/crypto/Makefile.am $libressl_path/crypto/Makefile.am
cp $script_path/crypto/objects/obj_dat.h $libressl_path/crypto/objects/obj_dat.h # no modifications for now
cp $script_path/crypto/CMakeLists.txt $libressl_path/crypto/CMakefile.txt
cp $script_path/crypto/Makefile.in $libressl_path/crypto/Makefile.in
cp $script_path/crypto/Makefile $libressl_path/crypto/Makefile

#################################################
##### libressl/include/openssl
cp $script_path/include/openssl/aria.h $libressl_path/include/openssl/aria.h

# Modifiyng makefiles and other files
cp $script_path/include/openssl/Makefile.am $libressl_path/include/openssl/Makefile.am
cp $script_path/include/openssl/obj_mac.h $libressl_path/include/openssl/obj_mac.h  # no modifications for now
cp $script_path/include/openssl/Makefile.in $libressl_path/include/openssl/Makefile.in
