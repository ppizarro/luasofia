#!/bin/sh
#set -x

rm -rf config.cache autom4te.cache 2> /dev/null
mkdir -p build-aux

#echo "Adding libtools."
libtoolize -c --force --automake

echo "Building macros."
aclocal

#echo "Building config header."
#autoheader

echo "Building makefiles."
automake -c --gnu --add-missing

echo "Building configure."
autoconf

