TOPDIR = ..
include $(TOPDIR)/mk/common.mk

DEMO = libdemo.a

all : $(DEMO)

$(DEMO) : char.o vesa.o
	$(Q)$(ECHO) "[AR] $@"
	$(Q)$(AR) cr $@ $^

char.o : char.c
	$(Q)$(ECHO) "[CC] $@"
	$(Q)$(CC) -o $@ $(CFLAGS) $(CODE16GCC) -c $^

vesa.o : vesa.c
	$(Q)$(ECHO) "[CC] $@"
	$(Q)$(CC) -o $@ $(CFLAGS) $(CODE16GCC) -c $^
	
clean:
	$(Q)$(RM) $(DEMO)
	$(Q)$(RM) char.o
	$(Q)$(RM) vesa.o
