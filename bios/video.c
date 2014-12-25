#include <video.h>

inline void set_cursor_shape(uint8 start, uint8 end, uint8 options)
{
	uint16 cx = ((start & 0x0F) << 8) | (end & 0x0F) | ((options & 0x03) << 13);
asm(
	"mov $0x01, %%ah\n"
	"mov %0, %%cx\n"
	"int $0x10\n"
	::"g"(cx)
	:"%ah", "%cx", "memory"
);
}

inline void get_cursor_info(uint8 page, struct cursor_info* info)
{
	uint8 start = 0;
	uint8 end = 0;
	uint8 row = 0;
	uint8 col = 0;
asm(
	"mov $0x03, %%ah\n"
	"mov %4, %%bh\n"
	"int $0x10\n"
	"mov %%ch, %0\n"
	"mov %%cl, %1\n"
	"mov %%dh, %2\n"
	"mov %%dl, %3\n"
	:"=m"(start), "=m"(end), "=m"(row), "=m"(col)
	:"g"(page)
	:"%ax", "%bh", "%cx", "%dx"
);
	info->start = start;
	info->end = end;
	info->row = row;
	info->col = col;
}

inline void tele_char(uint8 c, uint8 page, uint8 color)
{
asm(
	"mov $0x0E, %%ah\n"
	"mov %0, %%al\n"
	"mov %1, %%bh\n"
	"mov %2, %%bl\n"
	"int $0x10\n"
	::"g"(c), "g"(page), "g"(color)
	:"%ax", "%bx", "memory"
);
}

inline void tele_string(char* s, uint16 size, uint8 row, uint8 col, uint8 page, uint8 mode, union disp_attrib attrib)
{
	mode &= 0x03;
	uint8 bl = attrib.all;
	uint16 es = (uint32)s >> 16;
asm(
	"mov %%ds, %%ax\n"	// make sure that %es == %ds by default
	"mov %%ax, %%es\n"
	"mov %0, %%ax\n"	// if s is a far pointer
	"cmp $0, %%ax\n"	// in other words, the val es (%0) is not 0
	"je 1f\n"
	"mov %%ax, %%es\n"	// we push it into %es
	"1:\n"
	"mov $0x13, %%ah\n"
	"mov %1, %%al\n"
	"mov %2, %%bh\n"
	"mov %3, %%bl\n"
	"mov %4, %%cx\n"
	"mov %5, %%dh\n"
	"mov %6, %%dl\n"
	"mov %7, %%bp\n"
	"int $0x10\n"
	::"g"(es), "g"(mode), "g"(page), "g"(bl), "g"(size), "g"(row), "g"(col), "g"(s)
	:"%ax", "%bx", "%cx", "%dx", "%bp", "memory", "cc"
);
}

inline int get_svga_info(struct svga_info* info)
{
	uint16 ret = 0;
asm(
	"mov $0x4F00, %%ax\n"
	"mov %1, %%di\n"
	"int $0x10\n"
	"mov %%ax, %0"
	::"g"(ret), "g"(info)
	:"%ax", "%di", "memory"
);

	if ((ret & 0xFF) == 0x4F) {
		return ret >> 8;
	} else {
		return 2;
	}
}
