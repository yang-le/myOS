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

/*
 * Here we provide a default mouse callback func
 */

static int16 cur_x = 0, cur_y = 0;
static unsigned char mouse_cursor[] =
{	// size = 16 x 8
	69, 0, 0, 0, 0, 0, 0, 0,
	69, 0, 0, 0, 0, 0, 0, 0,
	69, 69, 0, 0, 0, 0, 0, 0,
	69, 255, 0, 0, 0, 0, 0, 0,
	69, 255, 69, 0, 0, 0, 0, 0,
	69, 255, 255, 0, 0, 0, 0, 0,
	69, 255, 255, 69, 0, 0, 0, 0,
	69, 255, 255, 255, 0, 0, 0, 0,
	69, 255, 255, 255, 69, 0, 0, 0,
	69, 255, 255, 255, 255, 0, 0, 0,
	69, 255, 255, 255, 69, 0, 0, 0,
	69, 255, 255, 69, 0, 0, 0, 0,
	69, 255, 69, 0, 0, 0, 0, 0,
	69, 69, 0, 255, 0, 0, 0, 0,
	69, 0, 0, 0, 255, 0, 0, 0,
	0, 0, 0, 255, 0, 0, 0, 0
};

void default_mouse_callback(union mouse_status status, uint16 _x, uint16 _y)
{
	int8 x = _x & 0xFF;
	int8 y = _y & 0xFF;
	uint32 color = RGB(0, 0, 0);

 	draw_rect(cur_x, cur_y, color, 16, 8);
	cur_x += x; cur_y -= y;
	if (cur_x < 0) cur_x = 0; if (cur_x > 1023) cur_x = 1023;
	if (cur_y < 0) cur_y = 0; if (cur_y > 767) cur_y = 767;
	if (status.left_button) color |= RGB(255, 0, 0);
	if (status.middle_button) color |= RGB(0, 255, 0);	
	if (status.right_button) color |= RGB(0, 0, 255);
	if ((color & 0x00FFFFFF) == 0) color = RGB(255, 255, 255);
	draw_bitmap(cur_x, cur_y, color, mouse_cursor, 16, 8);
}
