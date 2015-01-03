#include <bios.h>
#include <char.h>
#include <graphic.h>
#include "mouse.h"

//#define idle_wait() asm("hlt\n")
#define idle_wait() cursor_blink()

void my_os(void)
{
	puts("hello mouse!\r\n\r\n");
	graphic_init();
	mouse_init();
	set_mouse_callback(default_mouse_callback);
	
	int i = 0,j = 0;
	for (j = 0; j < 6; ++j)
		for (i = 0; i < 16; ++i)
			draw_char(i * 16, 100 + 16 * j, RGB(255, 255, 255), i + 16 * j);
}
