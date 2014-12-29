#include "keyboard.h"

// 00. KEYBOARD - GET KEYSTROKE
uint16 get_keystroke()
{
	uint16 ret = 0;
asm(
	"mov $0, %%ah\n"
	"int $0x16\n"
	"mov %%ax, %0\n"
	:"=m"(ret)
	::"%ax"
);
	return ret;
}
