#include <bios.h>
#include <graphic.h>
#include <stdio.h>

extern struct svga_mode_info graphic_info;
static uint16 cur_x = 0, cur_y = 0;

#define next_line(pix) \
	{cur_x = 0; if ((cur_y += (pix)) >= graphic_info.height) cur_y = 0;}

inline char getc()
{
	return get_keystroke();
}

int putchar(int c)
{
	if (graphic_info.mode_attrib.graphics) {
		if (c == '\r') {
			cur_x = 0;
			return;
		}
		if (c == '\n') {
			next_line(16);
			return;
		}
		if (c == '\b') {
			cur_x -= 16;
			draw_char(cur_x, cur_y, RGB(255, 255, 255), 0);
			cur_x -= 16;
			return;
		}
		if (c < ' ' || c > '~') c = '~' + 1;		
		draw_char(cur_x, cur_y, RGB(255, 255, 255), c - ' ');
		if ((cur_x += 16) >= graphic_info.width) next_line(16);
	} else {
		tele_char(c, 0, 0);
		if (c == '\r') tele_char('\n', 0, 0);
		if (c == '\b') {
			tele_char('\0', 0, 0);
			tele_char('\b', 0, 0);
		}
	}

	return c;
}

void htoa(uint8 hex)
{
	if (hex > 0xF) return;
	
	if (hex < 0xA)
		hex += '0';
	else
		hex += 'A' - 0xA;

	putchar(hex);
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
	if (graphic_info.mode_attrib.graphics) {
		const char* p = s;
		while(p && *p) putchar(*p++);
	} else {
		union disp_attrib attrib = {0};
		attrib.fcolor = COLOR_WHITE;
		
		struct cursor_info info = {0};
		get_cursor_info(0, &info);
		
		tele_string(s, strlen(s), info.row, info.col, 0, MODE_UPDATE_CURSOR, attrib);
	}
}

int printf(const char * fmt, ...)
{
	int ret;
	va_list va;
	va_start(va, fmt);
	char buffer[1024] = {0};
	ret = mini_vsnprintf(buffer, 1024, fmt, va);
	va_end(va);
	
	puts(buffer);
	return ret;
}

