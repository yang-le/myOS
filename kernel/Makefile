TOPDIR = ..
include $(TOPDIR)/mk/common.mk

KERNEL = libkernel.a

all : $(KERNEL)

$(KERNEL) : main.o mouse.o disk.o
	$(Q)$(ECHO) "[AR] $@"
	$(Q)$(AR) cr $@ $^

main.o : main.c
	$(Q)$(ECHO) "[CC] $@"
	$(Q)$(CC) -o $@ $(CFLAGS) $(CODE16GCC) -c $^

mouse.o : mouse.c
	$(Q)$(ECHO) "[CC] $@"
	$(Q)$(CC) -o $@ $(CFLAGS) $(CODE16GCC) -c $^

disk.o : disk.c
	$(Q)$(ECHO) "[CC] $@"
	$(Q)$(CC) -o $@ $(CFLAGS) $(CODE16GCC) -c $^

clean:
	$(Q)$(RM) $(KERNEL)
	$(Q)$(RM) main.o
	$(Q)$(RM) mouse.o
	$(Q)$(RM) disk.o
