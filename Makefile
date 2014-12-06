TOPDIR = .
include $(TOPDIR)/common.mk

all : myOS.bin

img : myOS.img

myOS.img : myOS.bin
	$(Q)mk_img.sh $@ $^

myOS.bin : myOS
	$(Q)objcopy -O binary -R .eh_fram -R .rdata -S $^ $@
	$(Q)cat $@ | wc -c > bin.size
	$(Q)echo "[SIZE] binary size = `cat bin.size`"
	$(Q)echo "[SIZE] fix boot code..."
	$(Q)cd boot && $(MAKE)
	$(Q)echo "[LINK] 2nd stage link..."
	$(Q)$(MAKE) link
	$(Q)-rm -f bin.size
	$(Q)objcopy -O binary -R .eh_fram -R .rdata -S $^ $@

myOS :
	$(Q)cd boot && $(MAKE)
	$(Q)cd kernel && $(MAKE)
	$(Q)cd char && $(MAKE)
	$(Q)cd bios && $(MAKE)
	$(Q)echo "[LINK] 1st stage link..."
	$(Q)$(MAKE) link

link : FORCE
	$(Q)ld -o myOS -nostdlib -T NUL boot/boot \
		-L./kernel -lkernel \
		-L./char -lchar \
		-L./bios -lbios

FORCE:

clean:
	$(Q)cd boot && $(MAKE) clean
	$(Q)cd kernel && $(MAKE) clean
	$(Q)cd char && $(MAKE) clean
	$(Q)cd bios && $(MAKE) clean
	$(Q)-rm -f myOS
	$(Q)-rm -f myOS.bin
	$(Q)-rm -f myOS.img
