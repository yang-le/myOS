#include <bios.h>
#include <char.h>
#include <graphic.h>
#include "mouse.h"

//#define idle_wait() asm("hlt\n")
#define idle_wait() cursor_blink()

int16 cur_x = 0, cur_y = 0;
static unsigned char mouse_cursor[] =
{	// size = 16 x 8
	'1', 0, 0, 0, 0, 0, 0, 0,
	'1', 0, 0, 0, 0, 0, 0, 0,
	'1', '1', 0, 0, 0, 0, 0, 0,
	'1', 'o', 0, 0, 0, 0, 0, 0,
	'1', 'o', '1', 0, 0, 0, 0, 0,
	'1', 'o', 'o', 0, 0, 0, 0, 0,
	'1', 'o', 'o', '1', 0, 0, 0, 0,
	'1', 'o', 'o', 'o', 0, 0, 0, 0,
	'1', 'o', 'o', 'o', '1', 0, 0, 0,
	'1', 'o', 'o', 'o', 'o', 0, 0, 0,
	'1', 'o', 'o', 'o', '1', 0, 0, 0,
	'1', 'o', 'o', '1', 0, 0, 0, 0,
	'1', 'o', '1', 0, 0, 0, 0, 0,
	'1', '1', 0, 'o', 0, 0, 0, 0,
	'1', 0, 0, 0, 'o', 0, 0, 0,
	0, 0, 0, 'o', 0, 0, 0, 0
};

void my_mouse_callback(union mouse_status status, uint16 _x, uint16 _y)
{
	int8 x = _x & 0xFF;
	int8 y = _y & 0xFF;
	uint32 color = RGB(0, 0, 0);

 	draw_rect(cur_x, cur_y, color, 16, 8);
	cur_x += x; cur_y -= y;
	if (cur_x < 0) cur_x = 0; if (cur_x > 1023) cur_x = 1023;
	if (cur_y < 0) cur_y = 0; if (cur_y > 767) cur_y = 767;
	if (status.left_button) color |= RGB(255, 0, 0);
	if (status.middle_button) color |= RGB(0, 255, 0);	
	if (status.right_button) color |= RGB(0, 0, 255);
	if ((color & 0x00FFFFFF) == 0) color = RGB(255, 255, 255);
	draw_bitmap(cur_x, cur_y, color, mouse_cursor, 16, 8);
}

void my_os(void)
{
	puts("hello mouse!\r\n\r\n");
	graphic_init();
	mouse_init();
	set_mouse_callback(my_mouse_callback);
	int i = 0;
	for (i = 0; i < 128; ++i)
	draw_char(i * 8, 100, RGB(255, 255, 255), i);
	//set_mouse_callback(null);
	//for(;;) idle_wait();
}
