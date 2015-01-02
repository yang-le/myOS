#include <bios.h>
#include <char.h>
#include <graphic.h>
#include "mouse.h"

//#define idle_wait() asm("hlt\n")
#define idle_wait() cursor_blink()

int16 cur_x = 0, cur_y = 0;
void my_mouse_callback(union mouse_status status, uint16 _x, uint16 _y)
{
	int8 x = _x & 0xFF;
	int8 y = _y & 0xFF;
	
 	set_pixel(cur_x, cur_y, RGB(0, 0, 0));
	cur_x += x; cur_y -= y;
	if (cur_x < 0) cur_x = 0; if (cur_x > 1023) cur_x = 1023;
	if (cur_y < 0) cur_y = 0; if (cur_y > 767) cur_y = 767;
	set_pixel(cur_x, cur_y, RGB(255, 255, 255));
}

void my_os(void)
{
	puts("hello mouse!\r\n\r\n");
	graphic_init();
	mouse_init();
	set_mouse_callback(my_mouse_callback);
	//set_mouse_callback(null);
	//for(;;) idle_wait();
}
