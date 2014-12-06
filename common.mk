ifeq ($(V), 1)
  Q =
  MAKE = make V=1
else
  Q = @
  MAKE = make
endif
