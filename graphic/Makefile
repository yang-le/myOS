TOPDIR = ..
include $(TOPDIR)/mk/common.mk

GRAPHIC = libgraphic.a

all : $(GRAPHIC)

$(GRAPHIC) : pixel.o core.o
	$(Q)$(ECHO) "[AR] $@"
	$(Q)$(AR) cr $@ $^

core.o : core.c
	$(Q)$(ECHO) "[CC] $@"
	$(Q)$(CC) -o $@ $(CFLAGS) $(CODE16GCC) -c $^

pixel.o : pixel.c
	$(Q)$(ECHO) "[CC] $@"
	$(Q)$(CC) -o $@ $(CFLAGS) $(CODE16GCC) -c $^
	
clean:
	$(Q)$(RM) $(GRAPHIC)
	$(Q)$(RM) core.o
	$(Q)$(RM) pixel.o
