#include <video.h>

inline void set_cursor_shape(uint8 start, uint8 end, uint8 options)
{
	uint16 cx = ((start & 0x0F) << 8) | (end & 0x0F) | ((options & 0x03) << 13);
asm(
	"mov $0x01, %%ah\n"
	"mov %0, %%cx\n"
	"int $0x10\n"
	::"g"(cx)
	:"%ah", "%cx"
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
	:"%ax", "%bh", "%cx", "%dx", "memory"
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
	:"%ax", "%bx"
);
}

inline void tele_string(const uint8* s, uint16 size, uint8 row, uint8 col, uint8 page, uint8 mode, union disp_attrib attrib)
{
	mode &= 0x03;
	uint8 bl = attrib.all;
asm(
	"mov $0x13, %%ah\n"
	"mov %0, %%al\n"
	"mov %1, %%bh\n"
	"mov %2, %%bl\n"
	"mov %3, %%cx\n"
	"mov %4, %%dh\n"
	"mov %5, %%dl\n"
	"mov %6, %%bp\n"
	"int $0x10\n"
	::"g"(mode), "g"(page), "g"(bl), "g"(size), "g"(row), "g"(col), "g"(s)
	:"%ax", "%bx", "%cx", "%dx", "%bp", "memory"
);
}
