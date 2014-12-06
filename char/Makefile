TOPDIR = ..
include $(TOPDIR)/common.mk

CHAR = libchar.a

all : $(CHAR)

$(CHAR) : char.o
	$(Q)echo "[AR] $@"
	$(Q)ar cr $@ $^

char.o : code16gcc.s char.c
	$(Q)echo "[CC] $@"
	$(Q)cc -o $@ -m32 -fno-builtin -nostdinc -c -Wa,$^

code16gcc.s:
	$(Q)echo .code16gcc > $@

clean:
	$(Q)-rm -f $(CHAR)
	$(Q)-rm -f char.o
	$(Q)-rm -f code16gcc.s
