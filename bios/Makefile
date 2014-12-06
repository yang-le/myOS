TOPDIR = ..
include $(TOPDIR)/common.mk

BIOS = libbios.a

all : $(BIOS)

$(BIOS) : 10.o 15.o
	$(Q)echo "[AR] $@"
	$(Q)ar cr $@ $^

10.o : code16gcc.s 10.c
	$(Q)echo "[CC] $@"
	$(Q)cc -o $@ -m32 -fno-builtin -nostdinc -c -Wa,$^

15.o : code16gcc.s 15.c
	$(Q)echo "[CC] $@"
	$(Q)cc -o $@ -m32 -fno-builtin -nostdinc -c -Wa,$^

code16gcc.s:
	$(Q)echo .code16gcc > $@

clean:
	$(Q)-rm -f $(BIOS)
	$(Q)-rm -f 10.o
	$(Q)-rm -f 15.o
	$(Q)-rm -f code16gcc.s
