#include <bios.h>
#include <char.h>
#include <graphic.h>
#include "mouse.h"

//#define idle_wait() asm("hlt\n")
#define idle_wait() cursor_blink()

void my_os(void)
{
	graphic_init();
	puts("hello mouse!\r\n\r\n");
	mouse_init();
	set_mouse_callback(default_mouse_callback);
	//show_svga_info();
}
