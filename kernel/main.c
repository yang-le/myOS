#include <bios.h>
#include <char.h>
#include <graphic.h>

//#define idle_wait() asm("hlt\n")
#define idle_wait() cursor_blink()

void my_mouse_callback(uint16 status, uint16 x, uint16 y)
{
	puts("status = ");dumpword(status);
	puts(" x = ");dumpword(x);
	puts(" y = ");dumpword(y);
	puts("\r\n");
}

void my_os(void)
{
	puts("hello mouse!\r\n\r\n");
	mouse_init();
	set_mouse_callback(my_mouse_callback);
	//set_mouse_callback(null);
	//for(;;) idle_wait();
}
