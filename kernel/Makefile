TOPDIR = ..
include $(TOPDIR)/common.mk

KERNEL = libkernel.a

all : $(KERNEL)

$(KERNEL) : main.o
	$(Q)echo "[AR] $@"
	$(Q)ar cr $@ $^

main.o : code16gcc.s main.c
	$(Q)echo "[CC] $@"
	$(Q)cc -o $@ -I../char -I../bios -m32 -fno-builtin -nostdinc -c -Wa,$^

code16gcc.s:
	$(Q)echo .code16gcc > $@

clean:
	$(Q)-rm -f $(KERNEL)
	$(Q)-rm -f main.o
	$(Q)-rm -f code16gcc.s
