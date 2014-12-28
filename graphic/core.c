// this file hold the global graphic varibles
#include <char.h>
#include <bios.h>
#include "core.h"

struct svga_mode_info graphic_info = {0};

void start_graphic_mode(uint16 mode, bool cls)
{
	int ret = 0;
	
	struct svga_info svga = {0};
	if (ret = get_svga_info(&svga)) {
		puts("get_svga_info failed, return val is ");
		dumpbyte(ret);
		puts("\r\n");
		return;
	}

	if (ret = get_svga_mode_info(mode, &graphic_info)) {
		puts("get_svga_mode_info failed, return val is ");
		dumpbyte(ret);
		puts("\r\n");
		return;
	}
	
 	if (ret = set_svga_mode(mode, cls)) {
		puts("set_svga_mode failed, return val is ");
		dumpbyte(ret);
		puts("\r\n");
		return;
	}
}

void graphic_init() {
	// mode 0x118 is 1024 x 768 @ 24bit pixel (BGR)
	// char cell width = 8 and height = 16, so can hold 48 rows and 128 cols
	// it has 64K single page, we choose it as default
	start_graphic_mode(GRAPHIC_MODE_1024x768x16M, true);
}
