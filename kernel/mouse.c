#include "mouse.h"
#include <graphic.h>

static mouse_callback mouse_cb = null;

static union mouse_status status = {0};
static uint16 x = 0, y = 0;
static uint8 count = 0;

/* 
 * RBIL says that this handler should have 4 param, each a word
 * word1 = status, word2 = x, word3 = y, word4 = z
 * but according to my experiment, bios will call this function 3 times
 * 1st time param's high byte will be the status
 * 2nd time param's high byte will be the x
 * 3rd time param's high byte will be the y
 * other bytes are all 0
 */
static void mouse_process(uint32 reserved, uint32 param)
{
asm(
	"mov %%cs, %%ax\n"	// fix ds, we rely on it to get mouse_cb
	"mov %%ax, %%ds\n"
	:::"%ax"
);
	if (mouse_cb == null) goto out;
	
	++count;
	if (1 == count) status.val = param >> 16;
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
	set_mouse_handler((far_ptr)mouse_process);
	init_mouse(3);	// i don't know why, but it works
	set_mouse_state(1);
}

void set_mouse_callback(mouse_callback func)
{
	mouse_cb = func;
}

static unsigned char mouse_cursor[16][8] =
{
	{'1', 'x', 'x', 'x', 'x', 'x', 'x', 'x'},
	{'1', 'x', 'x', 'x', 'x', 'x', 'x', 'x'},
	{'1', '1', 'x', 'x', 'x', 'x', 'x', 'x'},
	{'1', 'o', 'x', 'x', 'x', 'x', 'x', 'x'},
	{'1', 'o', '1', 'x', 'x', 'x', 'x', 'x'},
	{'1', 'o', 'o', 'x', 'x', 'x', 'x', 'x'},
	{'1', 'o', 'o', '1', 'x', 'x', 'x', 'x'},
	{'1', 'o', 'o', 'o', 'x', 'x', 'x', 'x'},
	{'1', 'o', 'o', 'o', '1', 'x', 'x', 'x'},
	{'1', 'o', 'o', 'o', 'o', 'x', 'x', 'x'},
	{'1', 'o', 'o', 'o', '1', 'x', 'x', 'x'},
	{'1', 'o', 'o', '1', 'x', 'x', 'x', 'x'},
	{'1', 'o', '1', 'x', 'x', 'x', 'x', 'x'},
	{'1', '1', 'x', 'o', 'x', 'x', 'x', 'x'},
	{'1', 'x', 'x', 'x', 'o', 'x', 'x', 'x'},
	{'x', 'x', 'x', 'o', 'x', 'x', 'x', 'x'},
};

void draw_mouse(uint16 x, uint16 y, uint32 color)
{
	int i, j;
	for (i = 0; i < 16; ++i) {
		for (j = 0; j < 8; ++j) {
			if (mouse_cursor[i][j] == 'x') set_pixel(x + j, y + i, 0);
			if (mouse_cursor[i][j] == '1') set_pixel(x + j, y + i, color);
			if (mouse_cursor[i][j] == 'o') set_pixel(x + j, y + i, color);
		}
	}
}
