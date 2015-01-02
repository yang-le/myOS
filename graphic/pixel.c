#include <bios.h>
#include "pixel.h"

extern struct svga_mode_info graphic_info;
uint8 cur_page = 0;

#define WIN_START_SEG (graphic_info.win_A_start_seg)
#define ROW_STEP (graphic_info.bytes_per_scanline)
#define COLOR_DEPTH (graphic_info.bits_per_pixel)
#define PAGE_SIZE (graphic_info.win_size << 10)
#define PAGE_GRAN (graphic_info.win_granularity << 10)

inline uint32 mix_color(uint32 fcolor, uint32 bcolor)
{
	uint8 a = (fcolor >> 24)& 0xFF;
	uint8 r = (a * ((fcolor >> 0)& 0xFF) + (255 - a) * ((bcolor >> 0)& 0xFF)) >> 8;
	uint8 g = (a * ((fcolor >> 8)& 0xFF) + (255 - a) * ((bcolor >> 8)& 0xFF)) >> 8;
	uint8 b = (a * ((fcolor >> 16)& 0xFF) + (255 - a) * ((bcolor >> 16)& 0xFF)) >> 8;
	return RGB(r, g, b);
}

void set_pixel(uint16 x, uint16 y, uint32 color)
{
	uint8 bytes_per_pixel = COLOR_DEPTH >> 3;
	uint32 pos = y * ROW_STEP + x * bytes_per_pixel;

	// correct cur_page first!!!
	if (pos / PAGE_GRAN != cur_page) {
		cur_page = pos / PAGE_GRAN;
		set_svga_mem_window(0, cur_page);
	}
	
	color = mix_color(color, get_pixel(x, y));
	uint8 r = (color >> 0)& 0xFF;
	uint8 g = (color >> 8)& 0xFF;
	uint8 b = (color >> 16)& 0xFF;

	pos %= PAGE_SIZE;
	if (pos + bytes_per_pixel > PAGE_SIZE) {	// we need to deal with in-pixel page switch
	asm(
		"mov %0, %%ax\n"
		"mov %%ax, %%fs\n"
		"mov %1, %%bx\n"
		"mov %2, %%al\n"
		"mov %%al, %%fs:(%%bx)\n"
		::"g"(WIN_START_SEG), "g"(pos), "g"(b)
		:"%ax", "%bx"
	);
		if (++pos >= PAGE_SIZE) {
			set_svga_mem_window(0, ++cur_page);	// change page in pixel
			pos = 0;
		}
	asm(
		"mov %0, %%ax\n"
		"mov %%ax, %%fs\n"
		"mov %1, %%bx\n"
		"mov %2, %%al\n"
		"mov %%al, %%fs:(%%bx)\n"
		::"g"(WIN_START_SEG), "g"(pos), "g"(g)
		:"%ax", "%bx"
	);
		if (++pos >= PAGE_SIZE) {
			set_svga_mem_window(0, ++cur_page);	// change page in pixel
			pos = 0;
		}
	asm(
		"mov %0, %%ax\n"
		"mov %%ax, %%fs\n"
		"mov %1, %%bx\n"
		"mov %2, %%al\n"
		"mov %%al, %%fs:(%%bx)\n"
		::"g"(WIN_START_SEG), "g"(pos), "g"(r)
		:"%ax", "%bx"
	);		
	} else {
	asm(
		"mov %0, %%ax\n"
		"mov %%ax, %%fs\n"
		"mov %1, %%bx\n"
		"mov %2, %%al\n"
		"mov %%al, %%fs:(%%bx)\n"
		"inc %%bx\n"
		"mov %3, %%al\n"
		"mov %%al, %%fs:(%%bx)\n"
		"inc %%bx\n"
		"mov %4, %%al\n"
		"mov %%al, %%fs:(%%bx)\n"
		::"g"(WIN_START_SEG), "g"(pos), "g"(b), "g"(g), "g"(r)
		:"%ax", "%bx"
	);
	}
}

uint32 get_pixel(uint16 x, uint16 y)
{
	uint8 bytes_per_pixel = COLOR_DEPTH >> 3;
	uint32 pos = y * ROW_STEP + x * bytes_per_pixel;

	// correct cur_page first!!!
	if (pos / PAGE_GRAN != cur_page) {
		cur_page = pos / PAGE_GRAN;
		set_svga_mem_window(0, cur_page);
	}
	
	uint8 r = 0;
	uint8 g = 0;
	uint8 b = 0;

	pos %= PAGE_SIZE;
	if (pos + bytes_per_pixel > PAGE_SIZE) {	// we need to deal with in-pixel page switch
	asm(
		"mov %1, %%ax\n"
		"mov %%ax, %%fs\n"
		"mov %2, %%bx\n"
		"mov %%fs:(%%bx), %%al\n"
		"mov %%al, %0\n"		
		:"=m"(b)
		:"g"(WIN_START_SEG), "g"(pos)
		:"%ax", "%bx", "memory"
	);
		if (++pos >= PAGE_SIZE) {
			set_svga_mem_window(0, ++cur_page);	// change page in pixel
			pos = 0;
		}
	asm(
		"mov %1, %%ax\n"
		"mov %%ax, %%fs\n"
		"mov %2, %%bx\n"
		"mov %%fs:(%%bx), %%al\n"
		"mov %%al, %0\n"		
		:"=m"(g)
		:"g"(WIN_START_SEG), "g"(pos)
		:"%ax", "%bx", "memory"
	);
		if (++pos >= PAGE_SIZE) {
			set_svga_mem_window(0, ++cur_page);	// change page in pixel
			pos = 0;
		}
	asm(
		"mov %1, %%ax\n"
		"mov %%ax, %%fs\n"
		"mov %2, %%bx\n"
		"mov %%fs:(%%bx), %%al\n"
		"mov %%al, %0\n"		
		:"=m"(r)
		:"g"(WIN_START_SEG), "g"(pos)
		:"%ax", "%bx", "memory"
	);		
	} else {
	asm(
		"mov %3, %%ax\n"
		"mov %%ax, %%fs\n"
		"mov %4, %%bx\n"
		"mov %%fs:(%%bx), %%al\n"
		"mov %%al, %0\n"		
		"inc %%bx\n"
		"mov %%fs:(%%bx), %%al\n"
		"mov %%al, %1\n"
		"inc %%bx\n"
		"mov %%fs:(%%bx), %%al\n"
		"mov %%al, %2\n"
		:"=m"(b), "=m"(g), "=m"(r)
		:"g"(WIN_START_SEG), "g"(pos)
		:"%ax", "%bx", "memory"
	);
	}
	return RGB(r, g, b);
}
