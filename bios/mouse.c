#include "mouse.h"

// C200. SYSTEM - POINTING DEVICE BIOS INTERFACE (PS) - ENABLE/DISABLE
inline int set_mouse_state(uint8 state)
{
	int ret = 0;
	state &= 1;
asm(
	"mov $0xC200, %%ax\n"
	"mov %1, %%bh\n"
	"int $0x15\n"
	"mov %%ah, %0\n"
	:"=m"(ret)
	:"g"(state)
	:"%ax", "%bh", "memory", "cc"
);
	return ret;
}

// C201. SYSTEM - POINTING DEVICE BIOS INTERFACE (PS) - RESET
#if 0
inline int reset_mouse(struct dev_info *info)
{
asm(
	"mov $0xC201, %%ax\n"
	"int $0x15\n"
	"mov %%ah, %0\n"
	"mov %%bh, %1\n"
	"mov %%bl, %2\n"
	:"=m"(ret), "=m"(info->id)
);
}
#endif
// C205. SYSTEM - POINTING DEVICE BIOS INTERFACE (PS) - INITIALIZE
inline int init_mouse(uint8 data_pack_size)
{
	int ret = 0;
	data_pack_size &= 8;
asm(
	"mov $0xC205, %%ax\n"
	"mov %1, %%bh\n"
	"int $0x15\n"
	"mov %%ah, %0"
	:"=m"(ret)
	:"g"(data_pack_size)
	:"%ax", "%bh", "memory", "cc"
);
	return ret;
}

// C207. SYSTEM - POINTING DEVICE BIOS INTERFACE (PS) - SET DEVICE HANDLER ADDR
inline int set_mouse_handler(far_ptr handler)
{
	int ret = 0;
	uint16 es = handler >> 16;
asm(
	"mov %%ds, %%ax\n"	// make sure that %es == %ds by default
	"mov %%ax, %%es\n"
	"mov %1, %%ax\n"	// if s is a far pointer
	"cmp $0, %%ax\n"	// in other words, the val es (%0) is not 0
	"je 1f\n"
	"mov %%ax, %%es\n"	// we push it into %es
	"1:\n"
	"mov %%cs, %%ax\n"
	"mov %%ax, %%es\n"
	"mov %2, %%bx\n"
	"mov $0xC207, %%ax\n"	
	"int $0x15\n"
	"mov %%ah, %0\n"
	:"=m"(ret)
	:"g"(es), "g"(handler)
	:"%ax", "%bx", "memory"
);
	return ret;
}
