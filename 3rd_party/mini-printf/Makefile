TOPDIR = ../..
include $(TOPDIR)/mk/common.mk

MINI-PRINTF = libmini-printf.a

all : $(MINI-PRINTF)

$(MINI-PRINTF) : mini-printf.o
	$(Q)$(ECHO) "[AR] $@"
	$(Q)$(AR) cr $@ $^

mini-printf.o : mini-printf.c
	$(Q)$(ECHO) "[CC] $@"
	$(Q)$(CC) -o $@ $(CFLAGS) $(CODE16GCC) -c $^
	
clean:
	$(Q)$(RM) $(MINI-PRINTF)
	$(Q)$(RM) mini-printf.o
	
