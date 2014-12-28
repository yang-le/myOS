#ifndef __GRAPHIC_PIXEL_H__
#define __GRAPHIC_PIXEL_H__

#include <graphic.h>

#define RGBA(r, g, b, a) ((r) | (g) << 8 | (b) << 16 | (a) << 24)
#define RGB(r, g, b) RGBA(r, g, b, 0)

void set_pixel(uint16 x, uint16 y, uint32 color);

#endif