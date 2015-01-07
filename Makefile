TOPDIR = .
include $(TOPDIR)/mk/common.mk

TARGET = myOS

all : $(TARGET).bin

img : $(TARGET).img

$(TARGET).img : $(TARGET).bin
	$(Q)mk/mk_img.sh $@ $^

$(TARGET).bin : $(TARGET)
	$(Q)$(OBJCP) $(OFLAGS) $^ $@
	$(Q)$(CAT) $@ | $(WC) -c > bin.size
	$(Q)$(ECHO) "[SIZE] binary size = `$(CAT) bin.size`"
	$(Q)$(ECHO) "[SIZE] fix boot code..."
	$(Q)$(MAKE) -C boot
	$(Q)$(ECHO) "[LINK] 2nd stage link..."
	$(Q)$(MAKE) link
	$(Q)$(RM) bin.size
	$(Q)$(OBJCP) $(OFLAGS) $^ $@

$(TARGET) : FORCE
	$(Q)$(MAKE) -C boot
	$(Q)$(MAKE) -C kernel
	$(Q)$(MAKE) -C demo	
	$(Q)$(MAKE) -C char
	$(Q)$(MAKE) -C graphic
	$(Q)$(MAKE) -C bios
	$(Q)$(ECHO) "[LINK] 1st stage link..."
	$(Q)$(MAKE) link

link : FORCE
	$(Q)$(LD) -o $(TARGET) $(LFLAGS) boot/boot boot/loader \
		-L./kernel -lkernel \
		-L./demo -ldemo \
		-L./char -lchar \
		-L./graphic -lgraphic \
		-L./bios -lbios

FORCE:

clean:
	$(Q)$(MAKE) -C boot clean
	$(Q)$(MAKE) -C kernel clean
	$(Q)$(MAKE) -C demo clean	
	$(Q)$(MAKE) -C char clean
	$(Q)$(MAKE) -C graphic clean
	$(Q)$(MAKE) -C bios clean
	$(Q)$(RM) $(TARGET)
	$(Q)$(RM) $(TARGET).bin
	$(Q)$(RM) $(TARGET).img
	$(Q)$(RM) system.map
