TOPDIR = ..
include $(TOPDIR)/common.mk

CHAR = libchar.a

all : $(CHAR)

$(CHAR) : char.o
	$(Q)$(ECHO) "[AR] $@"
	$(Q)$(AR) cr $@ $^

char.o : char.c
	$(Q)$(ECHO) "[CC] $@"
	$(Q)$(CC) -o $@ -m32 -fno-builtin -nostdinc $(CODE16GCC) -c $^

clean:
	$(Q)$(RM) -f $(CHAR)
	$(Q)$(RM) -f char.o
