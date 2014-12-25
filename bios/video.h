#ifndef __VIDEO_H__
#define __VIDEO_H__

#include <bios.h>

enum video_service_calls {
	vs_set_video_mode = 0x00,
	vs_set_cursor_shape,
	vs_set_cursor_pos,
	vs_get_cursor_info,
/*  vs_get_light_pen_pos, */
	vs_set_disp_page = 0x05,
	vs_scroll_up,
	vs_scroll_down,
	vs_get_curr_char_ex,
	vs_set_curr_char_ex,
	vs_set_curr_char,
	vs_set_bgcolor,
	vs_set_pixel,
	vs_get_pixel,
	vs_tele_char,
	vs_get_video_mode,
	vs_color,
	vs_font,
	vs_config,
	vs_tele_string
};

#define COLOR_BLACK (0)
#define COLOR_RED 	(1 << 2)
#define COLOR_GREEN (1 << 1)
#define COLOR_BLUE 	(1 << 0)

#define COLOR_YELLOW 	(COLOR_RED | COLOR_GREEN)
#define COLOR_CYAN 		(COLOR_GREEN | COLOR_BLUE)
#define COLOR_MAGENTA 	(COLOR_RED | COLOR_BLUE)
#define COLOR_WHITE 	(COLOR_RED | COLOR_GREEN | COLOR_BLUE)

union disp_attrib {
	struct {
		uint8 fcolor : 3;
		uint8 bright : 1;
		uint8 bcolor : 3;
		uint8 blink  : 1;
	};
	uint8 all;
};

struct cursor_info {
	uint8 start;
	uint8 end;
	uint8 row;
	uint8 col;
};

struct __attribute__ ((gcc_struct, packed)) svga_info {
	uint8 	signature[4];
	uint16	vesa_ver;
	uint32	oem;
	uint32	capability;
	uint32	support_vesa_oem_modes;
	uint16	mem_size;
	uint16	oem_ver;
	uint32	vendor_name;
	uint32	product_name;
	uint32	product_rev;
	uint16	vbe_af_ver;
	uint32	support_accelerate_modes;
	uint8	reserved[216];
	uint8	oem_scratchpad[256];
};

// start = 0 ~ 15
// end = 0 ~ 15
// options = 0 ~ 3
#define SHAPE_NORMAL 	0
#define SHAPE_INVISIBLE 1
#define SHAPE_ERRATIC 	2
#define SHAPE_SLOW 		3
void set_cursor_shape(uint8 start, uint8 end, uint8 options);

void get_cursor_info(uint8 page, struct cursor_info* info);

void tele_char(uint8 c, uint8 page, uint8 color);

#define MODE_UPDATE_CURSOR 1
#define MODE_ATTRIB_IN_STRING 2
void tele_string(char* s, uint16 size, uint8 row, uint8 col, uint8 page, uint8 mode, union disp_attrib attrib);

int get_svga_info(struct svga_info* info);

#endif