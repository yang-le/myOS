CHAR = libchar.a

all : $(CHAR)

$(CHAR) : char.o
	ar cr $@ $^

char.o : code16gcc.s char.c
	cc -o $@ -m32 -fno-builtin -nostdinc -c -Wa,$^

code16gcc.s:
	echo .code16gcc > $@

clean:
	-rm -f $(CHAR)
	-rm -f char.o
	-rm -f code16gcc.s
