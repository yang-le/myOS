TOPDIR = ..
include $(TOPDIR)/mk/common.mk

BIOS = libbios.a

all : $(BIOS)

$(BIOS) : video.o vesa.o misc.o keyboard.o
	$(Q)$(ECHO) "[AR] $@"
	$(Q)$(AR) cr $@ $^

video.o : video.c
	$(Q)$(ECHO) "[CC] $@"
	$(Q)$(CC) -o $@ $(CFLAGS) $(CODE16GCC) -c $^

vesa.o : vesa.c
	$(Q)$(ECHO) "[CC] $@"
	$(Q)$(CC) -o $@ $(CFLAGS) $(CODE16GCC) -c $^

misc.o : misc.c
	$(Q)$(ECHO) "[CC] $@"
	$(Q)$(CC) -o $@ $(CFLAGS) $(CODE16GCC) -c $^

keyboard.o : keyboard.c
	$(Q)$(ECHO) "[CC] $@"
	$(Q)$(CC) -o $@ $(CFLAGS) $(CODE16GCC) -c $^

clean:
	$(Q)$(RM) $(BIOS)
	$(Q)$(RM) video.o
	$(Q)$(RM) vesa.o	
	$(Q)$(RM) misc.o
	$(Q)$(RM) keyboard.o
	