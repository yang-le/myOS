all : boot.bin

img : boot.img

boot.o : boot.s
	as -o $@ $^

main.o : main.c
	cc -o $@ -m32 -Wa,code16gcc.h -nostdinc -c $^

boot : boot.o main.o
	ld -o $@ -nostdlib -T NUL $^

boot.bin : boot
	objcopy -O binary -R .eh_fram -R .rdata -S $^ $@

boot.img : boot.bin
	dd if=$^ 		of=$@ bs=1k 		count=1
	dd if=/dev/zero of=$@ bs=1k seek=1 	count=1439

clean:
	-rm -f boot
	-rm -f boot.o
	-rm -f boot.bin
	-rm -f boot.img
	-rm -f main.o
