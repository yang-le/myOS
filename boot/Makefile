TOPDIR = ..
include $(TOPDIR)/common.mk

all : boot

boot : boot.s FORCE
	$(Q)$(ECHO) "[BOOT] create bootsector $@"
	$(Q)fixsize.sh boot.s | $(AS) -o $@

FORCE:
	
clean:
	$(Q)$(RM) -f boot
