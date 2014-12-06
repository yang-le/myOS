TOPDIR = ..
include $(TOPDIR)/common.mk

all : boot

boot : boot.s FORCE
	$(Q)echo "[BOOT] create bootsector $@"
	$(Q)sh fixsize.sh boot.s | as -o $@

FORCE:
	
clean:
	$(Q)-rm -f boot
