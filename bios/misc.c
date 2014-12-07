#include <misc.h>

void delay(uint32 ms)
{
uint16 dx = (ms * 1000) & 0xFFFF;
uint16 cx = ((ms * 1000) >> 16) & 0xFFFF;

asm(
	"mov $0x86, %%ah\n"
	"mov %0, %%cx\n"
	"mov %1, %%dx\n"
	"int $0x15\n"
	::"r"(cx), "r"(dx)
	:"%ah", "%cx", "%dx"
);
}
