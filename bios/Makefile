TOPDIR = ..
include $(TOPDIR)/common.mk

BIOS = libbios.a

all : $(BIOS)

$(BIOS) : 10.o 15.o
	$(Q)$(ECHO) "[AR] $@"
	$(Q)$(AR) cr $@ $^

10.o : 10.c
	$(Q)$(ECHO) "[CC] $@"
	$(Q)$(CC) -o $@ -m32 -fno-builtin -nostdinc $(CODE16GCC) -c $^

15.o : 15.c
	$(Q)$(ECHO) "[CC] $@"
	$(Q)$(CC) -o $@ -m32 -fno-builtin -nostdinc $(CODE16GCC) -c $^

clean:
	$(Q)$(RM) -f $(BIOS)
	$(Q)$(RM) -f 10.o
	$(Q)$(RM) -f 15.o
