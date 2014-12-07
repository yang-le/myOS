#include <char.h>

void my_os(void)
{
//	char_init();
	char str[] = "hello world!";
	puts(str);
	for(;;){
		delay(500);
		set_cursor_shape(0, 15, 0);
		delay(500);
		set_cursor_shape(0, 15, 1);
	}
}
