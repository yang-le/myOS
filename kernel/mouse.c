#include <bios.h>

typedef void (*mouse_callback)(uint16 status, uint16 x, uint16 y);
mouse_callback mouse_cb = null;

uint16 status = 0;
uint16 x = 0, y = 0;
uint8 count = 0;

void mouse_process(uint32 reserved, uint32 param)
{
asm(
	"mov %%cs, %%ax\n"	// fix ds
	"mov %%ax, %%ds\n"
	:::"%ax"
);
	if (mouse_cb == null) goto out;
	
	++count;
	if (1 == count) status = param >> 16;
	if (2 == count) x = param >> 16;
	if (3 == count) {
		y = param >> 16;
		mouse_cb(status, x, y);
		count = 0;
	}
out:
asm(
	"add $0x18, %esp\n" // this generate a 'normal' retf to bios
	"pop %ebx\n"
	"lretw\n"
);
}

void mouse_init()
{
	int ret = set_mouse_handler((far_ptr)mouse_process);
	dumpword(ret);
//	ret = init_mouse(3);
//	dumpword(ret);
	ret = set_mouse_state(1);
	dumpword(ret);
	puts("\r\n");
}

void set_mouse_callback(mouse_callback func)
{
	mouse_cb = func;
}
