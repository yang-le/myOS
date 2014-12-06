TOPDIR = .
include $(TOPDIR)/common.mk

all : myOS.bin

img : myOS.img

myOS.img : myOS.bin
	$(Q)mk_img.sh $@ $^

myOS.bin : myOS
	$(Q)$(OBJCP) -O binary -R .eh_fram -R .rdata -S $^ $@
	$(Q)$(CAT) $@ | wc -c > bin.size
	$(Q)$(ECHO) "[SIZE] binary size = `$(CAT) bin.size`"
	$(Q)$(ECHO) "[SIZE] fix boot code..."
	$(Q)$(MAKE) -C boot
	$(Q)$(ECHO) "[LINK] 2nd stage link..."
	$(Q)$(MAKE) link
	$(Q)-$(RM) -f bin.size
	$(Q)$(OBJCP) -O binary -R .eh_fram -R .rdata -S $^ $@

myOS :
	$(Q)$(MAKE) -C boot
	$(Q)$(MAKE) -C kernel
	$(Q)$(MAKE) -C char
	$(Q)$(MAKE) -C bios
	$(Q)$(ECHO) "[LINK] 1st stage link..."
	$(Q)$(MAKE) link

link : FORCE
	$(Q)$(LD) -o myOS -nostdlib -T NUL boot/boot \
		-L./kernel -lkernel \
		-L./char -lchar \
		-L./bios -lbios

FORCE:

clean:
	$(Q)$(MAKE) -C boot clean
	$(Q)$(MAKE) -C kernel clean
	$(Q)$(MAKE) -C char clean
	$(Q)$(MAKE) -C bios clean
	$(Q)$(RM) -f myOS
	$(Q)$(RM) -f myOS.bin
	$(Q)$(RM) -f myOS.img
