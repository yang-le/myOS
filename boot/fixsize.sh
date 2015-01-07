#! /bin/sh

if [ -s "../bin.size" ]; then
	SIZE=`cat ../bin.size`
	NUM=`expr $SIZE / 512 - 2`
	sed -e "/SED FIXME START/,/SED FIXME END/c\#define SYS_SIZE_IN_SECTOR $NUM" $1
else
	cat $1
fi
