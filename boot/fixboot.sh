#! /bin/sh

echo "void main(){}" | gcc -o foo.out -x c -
ELF=`file foo.out | grep -i elf`
rm -f foo.out

# elf don't like "_"
if [ "$ELF" ]; then
	sed -e "s/_load_system/load_system/" $1
else
	cat $1
fi
