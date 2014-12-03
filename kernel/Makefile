KERNEL = libkernel.a

all : $(KERNEL)

$(KERNEL) : main.o
	ar cr $@ $^

main.o : code16gcc.s main.c
	cc -o $@ -I../char -m32 -fno-builtin -nostdinc -c -Wa,$^

code16gcc.s:
	echo .code16gcc > $@

clean:
	-rm -f $(KERNEL)
	-rm -f main.o
	-rm -f code16gcc.s
