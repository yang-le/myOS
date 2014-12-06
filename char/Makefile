TOPDIR = ..
include $(TOPDIR)/mk/common.mk

CHAR = libchar.a

all : $(CHAR)

$(CHAR) : char.o
	$(Q)$(ECHO) "[AR] $@"
	$(Q)$(AR) cr $@ $^

char.o : char.c
	$(Q)$(ECHO) "[CC] $@"
	$(Q)$(CC) -o $@ $(CFLAGS) $(CODE16GCC) -c $^

clean:
	$(Q)$(RM) $(CHAR)
	$(Q)$(RM) char.o
