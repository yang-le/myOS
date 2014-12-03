all : kernel

kernel : main.o
	ld -o $@ -nostdlib -T NUL $^

main.o : code16gcc.s main.c
	cc -o $@ -m32 -nostdinc -c -Wa,$^

code16gcc.s:
	echo .code16gcc > $@

clean:
	-rm -f kernel
	-rm -f main.o
	-rm -f code16gcc.s
