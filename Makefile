all : myOS.bin

img : myOS.img

myOS.img : myOS.bin
	dd if=$^ 		of=$@ bs=1k 		count=1
	dd if=/dev/zero of=$@ bs=1k seek=1 	count=1439

myOS.bin : myOS
	objcopy -O binary -R .eh_fram -R .rdata -S $^ $@

myOS :
	cd boot && make && cd ..
	cd kernel && make && cd ..
	ld -o $@ -nostdlib -T NUL boot/boot kernel/kernel

clean:
	cd boot && make clean && cd ..
	cd kernel && make clean && cd ..
	-rm -f myOS
	-rm -f myOS.bin
	-rm -f myOS.img
