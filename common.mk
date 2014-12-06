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
RM = rm

CODE16GCC = -Wa,$(TOPDIR)/code16gcc.s
