TOPDIR = .
include $(TOPDIR)/mk/common.mk

TARGET = myOS

all : $(TARGET).bin

img : $(TARGET).img

$(TARGET).img : $(TARGET).bin
	$(Q)mk/mk_img.sh $@ $^

$(TARGET).bin : $(TARGET)
	$(Q)$(OBJCP) -O binary -R .eh_fram -R .rdata -S $^ $@
	$(Q)$(CAT) $@ | $(WC) -c > bin.size
	$(Q)$(ECHO) "[SIZE] binary size = `$(CAT) bin.size`"
	$(Q)$(ECHO) "[SIZE] fix boot code..."
	$(Q)$(MAKE) -C boot
	$(Q)$(ECHO) "[LINK] 2nd stage link..."
	$(Q)$(MAKE) link
	$(Q)$(RM) bin.size
	$(Q)$(OBJCP) -O binary -R .eh_fram -R .rdata -S $^ $@

$(TARGET) : FORCE
	$(Q)$(MAKE) -C boot
	$(Q)$(MAKE) -C kernel
	$(Q)$(MAKE) -C char
	$(Q)$(MAKE) -C bios
	$(Q)$(ECHO) "[LINK] 1st stage link..."
	$(Q)$(MAKE) link

link : FORCE
	$(Q)$(LD) -o $(TARGET) $(LFLAGS) boot/boot \
		-L./kernel -lkernel \
		-L./char -lchar \
		-L./bios -lbios

FORCE:

clean:
	$(Q)$(MAKE) -C boot clean
	$(Q)$(MAKE) -C kernel clean
	$(Q)$(MAKE) -C char clean
	$(Q)$(MAKE) -C bios clean
	$(Q)$(RM) $(TARGET)
	$(Q)$(RM) $(TARGET).bin
	$(Q)$(RM) $(TARGET).img
