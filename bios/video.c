#include "video.h"

// 00. VIDEO - SET VIDEO MODE
inline int set_video_mode(uint8 mode, bool cls)
{
	uint8 ret = 0;
	if (!cls) mode |= 1 << 7;
asm(
	"mov $0x00, %%ah\n"
	"mov %1, %%al\n"
	"int $0x10\n"
	"mov %%al, %0"
	:"=m"(ret)
	:"g"(mode)
	:"%ax", "memory"
);

	return ret;
}

// 01. VIDEO - SET TEXT-MODE CURSOR SHAPE
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

// 03. VIDEO - GET CURSOR POSITION AND SIZE
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

// 0A. VIDEO - WRITE CHARACTER ONLY AT CURSOR POSITION
inline void write_char(uint8 c, uint8 page, uint8 color, uint16 rep_count)
{
asm(
	"mov $0x0A, %%ah\n"
	"mov $0, %%al\n"
	"mov $1, %%bh\n"
	"mov $2, %%bl\n"
	"mov $3, %%cx\n"
	"int $0x10\n"
	::"g"(c), "g"(page), "g"(color), "g"(rep_count)
	:"%ax", "%bx", "%cx", "memory"
);
}

// 0C. VIDEO - WRITE GRAPHICS PIXEL
inline void write_pixel(uint8 p, uint8 page, uint16 col, uint16 row)
{
asm(
	"mov $0x0C, %%ah\n"
	"mov %0, %%al\n"
	"mov %1, %%bh\n"
	"mov %2, %%cx\n"
	"mov %3, %%dx\n"
	"int $0x10\n"
	::"g"(p), "g"(page), "g"(col), "g"(row)
	:"%ax", "%bh", "%cx", "%dx"
);
}

// 0E. VIDEO - TELETYPE OUTPUT
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

// 0F. VIDEO - GET CURRENT VIDEO MODE
inline int get_video_mode(struct video_mode_info* info)
{
	uint8 cols;
	uint8 mode;
	uint8 page;
asm(
	"mov $0x0F, %%ah\n"
	"int $0x10\n"
	"mov %%ah, %0\n"
	"mov %%al, %1\n"
	"mov %%bh, %2\n"
	:"=m"(cols), "=m"(mode), "=m"(page)
	::"%ax", "%bx", "memory"
);
	info->cols = cols;
	info->disp_mode = mode;
	info->cur_page = page;
}

// 13. VIDEO - WRITE STRING (AT and later,EGA)
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

#include "vesa.c"
