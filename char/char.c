inline void char_init(void)
{
asm(
	"mov $0xb800, %ax\n"
	"mov %ax, %es\n"
	"xor %di, %di\n"
);	
}

inline void putc(const char c)
{
asm(
	"movb %0, %%es:(%%di)\n"
	"add $2, %%di\n"
	::"a"(c)
);
}

void htoa(unsigned char hex)
{
	if (hex < 0xA)
		hex += '0';
	else
		hex += 'A' - 0xA;

	putc(hex);
}

void dumpbyte(const char b)
{
	htoa((b >> 4) & 0xf);
	htoa((b >> 0) & 0xf);
}

void dumptr(const void* p)
{
	unsigned long val = (unsigned long)p;
	dumpbyte((val >> 24) & 0xff);
	dumpbyte((val >> 16) & 0xff);
	dumpbyte((val >> 8)  & 0xff);
	dumpbyte((val >> 0)	 & 0xff);
}

void puts(const char* s)
{
	const char* p = s;
	while(p && *p)
		putc(*p++);
}