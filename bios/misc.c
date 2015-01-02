#include "misc.h"

// 86. BIOS - WAIT (AT,PS)
inline void delay(uint32 ms)
{
	uint16 dx = (ms * 1000) & 0xFFFF;
	uint16 cx = ((ms * 1000) >> 16) & 0xFFFF;
asm(
	"mov $0x86, %%ah\n"
	"mov %0, %%cx\n"
	"mov %1, %%dx\n"
	"int $0x15\n"
	::"g"(cx), "g"(dx)
	:"%ah", "%cx", "%dx"
);
}
#if 0
// C0. SYSTEM - GET CONFIGURATION
inline int get_sys_config(far_ptr *p)
{
	int ret = 0;
	uint16 base = 0;
	uint16 offset = 0;
asm(
	"mov $0xC0, %%ah\n"
	"int $0x15\n"
	"mov %%bx, %0\n"
	"mov %%es, %1\n"
	"mov %%ah, %2\n"
	:"=m"(offset), "=m"(base), "=m"(ret)
	::"%ax", "%bx", "memory", "cc"
);
	*p = (base << 16) | offset;
	return ret;
}
#endif
#include "mouse.c"
