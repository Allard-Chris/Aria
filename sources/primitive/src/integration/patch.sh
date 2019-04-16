#! /bin/sh
# This bash will create the patch file for aria inside libressl

# Pour créer un patch entre deux fichiers, il suffit de taper la commande :
# diff -u fichier1 fichier2 > mon.patch

# Patcher tous les fichiers indiqués par le patch
# patch < mon.patch

# Important Path for patching
libressl_path="../../../libressl-2.9.0"
script_path=. #"$( cd "$(dirname "$0")" ; pwd -P )"

patch=""

#################################################
##### libressl/app/openssl
patch=$patch"\n"$(diff -u $script_path/apps/openssl/openssl.c $libressl_path/apps/openssl/openssl.c)
patch=$patch"\n"$(diff -u $script_path/apps/openssl/genrsa.c $libressl_path/apps/openssl/genrsa.c)
patch=$patch"\n"$(diff -u $script_path/apps/openssl/gendsa.c $libressl_path/apps/openssl/gendsa.c)
patch=$patch"\n"$(diff -u $script_path/apps/openssl/smime.c $libressl_path/apps/openssl/smime.c)
patch=$patch"\n"$(diff -u $script_path/apps/openssl/pkcs12.c $libressl_path/apps/openssl/pkcs12.c)
patch=$patch"\n"$(diff -u $script_path/apps/openssl/speed.c $libressl_path/apps/openssl/speed.c)

#################################################
##### libressl/crypto
# Creating folder for aria primitive
#mkdir $libressl_path/crypto/aria
#mkdir $libressl_path/crypto/aria/.deps

# Copy all aria files on crypto/aria
patch=$patch"\n"$(diff -u --new-file $script_path/crypto/aria/aria_core.c $libressl_path/crypto/aria/aria_core.c)
patch=$patch"\n"$(diff -u --new-file $script_path/crypto/aria/aria_locl.h $libressl_path/crypto/aria/aria_locl.h)

# Modifiyng makefiles and other files
patch=$patch"\n"$(diff -u $script_path/crypto/Makefile.am $libressl_path/crypto/Makefile.am)
patch=$patch"\n"$(diff -u $script_path/crypto/objects/obj_dat.h $libressl_path/crypto/objects/obj_dat.h) # no modifications for now
patch=$patch"\n"$(diff -u --new-file $script_path/crypto/CMakeLists.txt $libressl_path/crypto/CMakefile.txt)
patch=$patch"\n"$(diff -u $script_path/crypto/Makefile.in $libressl_path/crypto/Makefile.in)
patch=$patch"\n"$(diff -u $script_path/crypto/crypto.sym $libressl_path/crypto/crypto.sym)

#cp $script_path/crypto/Makefile $libressl_path/crypto/Makefile # created by .configure command
#cp $script_path/crypto/.deps/XXX $libressl_path/crypto/.deps/XXX

#################################################
##### libressl/include/openssl
patch=$patch"\n"$(diff -u --new-file $script_path/include/openssl/aria.h $libressl_path/include/openssl/aria.h)

# Modifiyng makefiles and other files
#patch=$patch"\n"$(diff -u $script_path/include/openssl/Makefile.am $libressl_path/include/openssl/Makefile.am)
patch=$patch"\n"$(diff -u $script_path/include/openssl/obj_mac.h $libressl_path/include/openssl/obj_mac.h)  # no modifications for now
patch=$patch"\n"$(diff -u $script_path/include/openssl/Makefile.in $libressl_path/include/openssl/Makefile.in)

echo $patch > aria.patch

#################################################
##### automatic patch creation

#for file in ./*; do
#    #echo $file
#    if [ $(basename $file) != "patch" ] && [ $(basename $file) != "patch.sh" ] && [ $(basename $file) != "patch_creation.sh" ]
#    then
#      for f in $file/*; do
#        echo "diff -u $f $libressl_path/$f"
#        patch=$patch\n$(diff -u $f $libressl_path/$f)
#        echo $(diff -u $f $libressl_path/$f)
#      done
#    fi
#done