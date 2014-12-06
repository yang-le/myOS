#ifndef __10_H__
#define __10_H__

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

// start = 0 ~ 15
// end = 0 ~ 15
// options = 0 ~ 3
//   0 = normal
//   1 = invisible
//   2 = erratic
//   3 = slow
void set_cursor_shape(unsigned char start, unsigned char end, unsigned char options);

#endif