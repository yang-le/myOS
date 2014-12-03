all : myOS.bin

img : myOS.img

myOS.img : myOS.bin
	dd if=$^ 		of=$@ bs=1k 		count=1
	dd if=/dev/zero of=$@ bs=1k seek=1 	count=1439

myOS.bin : myOS
	objcopy -O binary -R .eh_fram -R .rdata -S $^ $@

myOS : FORCE
	cd boot && make
	cd kernel && make
	cd char && make
	ld -o $@ -nostdlib -T NUL boot/boot \
		-L./kernel -lkernel \
		-L./char -lchar

FORCE:

clean:
	cd boot && make clean
	cd kernel && make clean
	cd char && make clean
	-rm -f myOS
	-rm -f myOS.bin
	-rm -f myOS.img
