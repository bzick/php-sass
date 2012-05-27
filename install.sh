#!/bin/sh

MOD_DIR=$(readlink -f $(dirname $0))
MOD_TMP=/tmp/sass

rm -rf $MOD_TMP

mkdir $MOD_TMP

if [ ! -d $MOD_TMP ]; then
	echo "Can't create tmp dir $MOD_TMP"
	exit 1;
fi

cp -r $MOD_DIR/* $MOD_TMP
cd $MOD_TMP


phpize
./configure --with-sass
make
make install
exit 0