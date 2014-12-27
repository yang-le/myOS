#include <bios.h>
#include <char.h>
#include <demo/vesa.h>

//#define idle_wait() asm("hlt\n")
#define idle_wait() cursor_blink()

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

	struct svga_mode_info info= {0};
	if (ret = get_svga_mode_info(mode, &info)) {
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

void my_os(void)
{
	puts("hello world!\r\n\r\n");
	puts("starting graphic mode...\r\n\r\n");
	
	dump_svga_mode(0x118, 2);
	//start_graphic_mode(0x118, true);

	puts("hello graphic!\r\n\r\n");
	
	
	for(;;) idle_wait();
}
