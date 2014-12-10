#! /bin/sh

echo "void main(){}" | gcc -o foo.out -x c -
ELF=`file foo.out | grep -i elf`
rm -f foo.out

# elf don't like "_"
if [ "$ELF" ]; then
SCMD="-e s/_my_os/my_os/"
fi

if [ -s "../bin.size" ]; then
	SIZE=`cat ../bin.size`
	NUM=`expr $SIZE / 512 + 1`
	sed -e "/SED FIXME START/,/SED FIXME END/c\movb \$$NUM, %al" $SCMD $1
elif [ "$ELF" ]; then
	sed $SCMD $1
else
	cat $1
fi
