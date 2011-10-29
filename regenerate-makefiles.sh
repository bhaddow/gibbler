#!/bin/bash

# NOTE:
# Versions 1.9 (or higher) of aclocal and automake are required.

# For Mac OSX users:
# Standard distribution usually includes versions 1.6.
# Get versions 1.9 or higher
# Set the following variable to the correct paths
#ACLOCAL="/path/to/aclocal-1.9"
#AUTOMAKE="/path/to/automake-1.9"

function die () {
  echo "$@" >&2
  exit 1
}

if [ -z "$ACLOCAL" ]
then
    ACLOCAL=`which aclocal`
fi

if [ -z "$AUTOMAKE" ]
then
    AUTOMAKE=`which automake`
fi

if [ -z "$AUTOCONF" ]
then
    AUTOCONF=`which autoconf`
fi

if [ -z "$LIBTOOLIZE" ]
then
    LIBTOOLIZE=`which libtoolize`
    
    if [ -z "$LIBTOOLIZE" ]
    then
        LIBTOOLIZE=`which glibtoolize`
    fi
fi


echo "Calling $ACLOCAL..."
$ACLOCAL -I m4 || die "aclocal failed"
echo "Calling $AUTOCONF..."
$AUTOCONF  || die "autoconf failed"
rm ltmain.sh 2>/dev/null
touch ltmain.sh
echo "Calling $AUTOMAKE..."
$AUTOMAKE || die "automake failed"
echo "Calling $LIBTOOLIZE"
$LIBTOOLIZE || die "libtoolize failed"

