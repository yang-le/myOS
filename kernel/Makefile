TOPDIR = ..
include $(TOPDIR)/common.mk

KERNEL = libkernel.a

all : $(KERNEL)

$(KERNEL) : main.o
	$(Q)$(ECHO) "[AR] $@"
	$(Q)$(AR) cr $@ $^

main.o : main.c
	$(Q)$(ECHO) "[CC] $@"
	$(Q)$(CC) -o $@ -I../char -I../bios -m32 -fno-builtin -nostdinc $(CODE16GCC) -c $^

clean:
	$(Q)$(RM) -f $(KERNEL)
	$(Q)$(RM) -f main.o
