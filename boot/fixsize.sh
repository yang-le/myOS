#! /bin/sh

if [ -a "../bin.size" ]; then
	SIZE=`cat ../bin.size`
	NUM=`expr $SIZE / 512 + 1`
	sed -e "/SED FIXME START/,/SED FIXME END/c\movb \$$NUM, %al" $1
else
	cat $1
fi
