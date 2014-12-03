#include "char.h"

void my_os(void)
{
	char_init();
	char str[] = "hello world!";
	puts(str);
	for(;;);
}
