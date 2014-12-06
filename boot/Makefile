TOPDIR = ..
include $(TOPDIR)/common.mk

all : boot

boot : boot.s FORCE
	$(Q)$(ECHO) "[BOOT] create bootsector $@"
	$(Q)sh fixsize.sh boot.s | $(AS) -o $@

FORCE:
	
clean:
	$(Q)$(RM) -f boot
