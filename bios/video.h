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

// 00. VIDEO - SET VIDEO MODE
int set_video_mode(uint8 mode, bool cls);

// 01. VIDEO - SET TEXT-MODE CURSOR SHAPE
#define SHAPE_NORMAL 	0
#define SHAPE_INVISIBLE 1
#define SHAPE_ERRATIC 	2
#define SHAPE_SLOW 		3

void set_cursor_shape(uint8 start, uint8 end, uint8 options);

// 03. VIDEO - GET CURSOR POSITION AND SIZE
struct cursor_info {
	uint8 start;
	uint8 end;
	uint8 row;
	uint8 col;
};

void get_cursor_info(uint8 page, struct cursor_info* info);

// 0A. VIDEO - WRITE CHARACTER ONLY AT CURSOR POSITION
inline void write_char(uint8 c, uint8 page, uint8 color, uint16 rep_count);

// 0C. VIDEO - WRITE GRAPHICS PIXEL
void write_pixel(uint8 p, uint8 page, uint16 col, uint16 row);

// 0E. VIDEO - TELETYPE OUTPUT
#define COLOR_BLACK (0)
#define COLOR_RED 	(1 << 2)
#define COLOR_GREEN (1 << 1)
#define COLOR_BLUE 	(1 << 0)

#define COLOR_YELLOW 	(COLOR_RED | COLOR_GREEN)
#define COLOR_CYAN 		(COLOR_GREEN | COLOR_BLUE)
#define COLOR_MAGENTA 	(COLOR_RED | COLOR_BLUE)
#define COLOR_WHITE 	(COLOR_RED | COLOR_GREEN | COLOR_BLUE)

void tele_char(uint8 c, uint8 page, uint8 color);

// 0F. VIDEO - GET CURRENT VIDEO MODE
struct video_mode_info {
	uint8 cols;
	uint8 disp_mode;
	uint8 cur_page;
};

int get_video_mode(struct video_mode_info* info);

// 13. VIDEO - WRITE STRING (AT and later,EGA)
#define MODE_UPDATE_CURSOR 1
#define MODE_ATTRIB_IN_STRING 2

union disp_attrib {
	uint8 all;
	struct {
		uint8 fcolor : 3;
		uint8 bright : 1;
		uint8 bcolor : 3;
		uint8 blink  : 1;
	};
};

void tele_string(char* s, uint16 size, uint8 row, uint8 col, uint8 page, uint8 mode, union disp_attrib attrib);

#include "vesa.h"

#endif
