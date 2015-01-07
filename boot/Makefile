TOPDIR = ..
include $(TOPDIR)/mk/common.mk

all : boot loader

boot : boot.s
	$(Q)$(ECHO) "[BOOT] create bootsector $@"
	$(Q)./fixboot.sh boot.s | $(CC) -o $@ -x assembler-with-cpp -c -

loader : loader.c FORCE
	$(Q)$(ECHO) "[LOADER] create loader $@"
	$(Q)./fixsize.sh loader.c | $(CC) -o $@ $(CFLAGS) $(CODE16GCC) -x c -c -

FORCE:

clean:
	$(Q)$(RM) boot
	$(Q)$(RM) loader
