TOPDIR = ..
include $(TOPDIR)/common.mk

BIOS = libbios.a

all : $(BIOS)

$(BIOS) : 10.o 15.o
	$(Q)$(ECHO) "[AR] $@"
	$(Q)$(AR) cr $@ $^

10.o : 10.c
	$(Q)$(ECHO) "[CC] $@"
	$(Q)$(CC) -o $@ $(CFLAGS) $(CODE16GCC) -c $^

15.o : 15.c
	$(Q)$(ECHO) "[CC] $@"
	$(Q)$(CC) -o $@ $(CFLAGS) $(CODE16GCC) -c $^

clean:
	$(Q)$(RM) $(BIOS)
	$(Q)$(RM) 10.o
	$(Q)$(RM) 15.o
