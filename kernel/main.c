#include <bios.h>
#include <char.h>
#include <graphic.h>
#include "mouse.h"
#include <stdio.h>

//#define idle_wait() asm("hlt\n")
#define idle_wait() cursor_blink()

void my_os(void)
{
	graphic_init();
	printf("hello %s %d %%\n", "world", 1);
	puts("hello new font!\r\n\r\n");
	mouse_init();
	set_mouse_callback(default_mouse_callback);
	int i = 0, j = 0;
	for (i = 0; i < 6; ++i) {
		for (j = 0; j < 16; ++j)
			putchar(' ' + i * 16 + j);
		puts("\r\n");
	}
}
