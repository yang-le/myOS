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

void dumpbyte(unsigned char b)
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

unsigned int strlen(const char* s)
{
	unsigned int l = 0;
	const char* p = s;
	while(p && *p++) ++l;
	return l;
}

void puts(const char* s)
{
	union disp_attrib attrib = {0};
	attrib.fcolor = COLOR_WHITE;
	
	struct cursor_info info = {0};
	get_cursor_info(0, &info);
	
	tele_string(s, strlen(s), info.row, info.col, 0, MODE_UPDATE_CURSOR, attrib);
}
