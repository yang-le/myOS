#ifndef __GRAPHIC_PIXEL_H__
#define __GRAPHIC_PIXEL_H__

#include <graphic.h>

#define RGBA(r, g, b, a) ((r) | (g) << 8 | (b) << 16 | (a) << 24)
#define RGB(r, g, b) RGBA(r, g, b, 255)

void set_pixel(uint16 x, uint16 y, uint32 color);
uint32 get_pixel(uint16 x, uint16 y);
uint32 mix_color(uint32 fcolor, uint32 bcolor);
void draw_bitmap(uint16 x, uint16 y, uint32 color, uint8 *bitmap, uint16 rows, uint16 cols);

#endif
