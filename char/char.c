#include <bios.h>

inline void putc(const char c)
{
	tele_char(c, 0, 0);
}

void htoa(unsigned char hex)
{
	if (hex > 0xF) return;
	
	if (hex < 0xA)
		hex += '0';
	else
		hex += 'A' - 0xA;

	putc(hex);
}

void dumpbyte(uint8 b)
{
	htoa((b >> 4) & 0xf);
	htoa((b >> 0) & 0xf);
}

void dumpword(uint16 w)
{
	dumpbyte((w >> 8) & 0xff);
	dumpbyte((w >> 0) & 0xff);	
}

void dumpdword(uint32 dw)
{
	dumpbyte((dw >> 24) & 0xff);
	dumpbyte((dw >> 16) & 0xff);
	dumpbyte((dw >> 8)  & 0xff);
	dumpbyte((dw >> 0)	& 0xff);
}

void dumptr(const void* p)
{
	uint32 val = (uint32)p;
	dumpdword(val);
}

unsigned int strlen(char* s)
{
	unsigned int l = 0;
	uint16 es = (uint32)s >> 16;
	
	if (es) {
	asm(
		"mov %1, %%ax\n"
		"mov %%ax, %%es\n"
		"mov %2, %%bx\n"
		"xor %%cx, %%cx\n"
		"1:\n"
		"mov %%es:(%%bx), %%al\n"
		"cmp $0, %%al\n"
		"je 1f\n"
		"inc %%bx\n"
		"inc %%cx\n"
		"jmp 1b\n"
		"1:\n"
		"mov %%cx, %0"
		:"=m"(l)
		:"g"(es), "g"(s)
		:"%ax", "%bx", "%cx", "memory", "cc"
	);
		return l;
	}
	
	const char* p = s;
	while(p && *p++) ++l;
	return l;
}

void puts(char* s)
{
	union disp_attrib attrib = {0};
	attrib.fcolor = COLOR_WHITE;
	
	struct cursor_info info = {0};
	get_cursor_info(0, &info);
	
	tele_string(s, strlen(s), info.row, info.col, 0, MODE_UPDATE_CURSOR, attrib);
}
