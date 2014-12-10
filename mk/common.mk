ifeq ($(V), 1)
  Q =
  MAKE = make V=1
else
  Q = @
  MAKE = make
endif

AS = as
CC = cc
AR = ar
LD = ld
OBJCP = objcopy

CAT = cat
DD = dd
ECHO = echo
SED = sed
RM = rm -f
WC = wc

CFLAGS = -m32 -fomit-frame-pointer -fno-builtin -nostdinc -I$(TOPDIR)/char -I$(TOPDIR)/bios
LFLAGS = -nostdlib -Ttext 0
OFLAGS = -O binary -R .eh_frame -R .eh_fram -R .comment -R .edata -R .idata -S

CODE16GCC = -Wa,$(TOPDIR)/mk/code16gcc.s
