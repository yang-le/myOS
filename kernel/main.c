#include <bios.h>
#include <char.h>

void color_test()
{
	puts("Color test\r\n");
	
	char color[][16] = {
		"black\r\n",
		"blue\r\n",
		"green\r\n",
		"cyan\r\n",
		"red\r\n",
		"magenta\r\n",
		"yellow\r\n",		
		"white\r\n"	
	};

	union disp_attrib attrib = {0};
	struct cursor_info info = {0};
	int i = 0;
	
	// give you some color to see see :-)
	for (; i <= COLOR_WHITE; ++i) {
		get_cursor_info(0, &info);
		attrib.fcolor = i;
		attrib.bcolor = COLOR_WHITE - i;
		tele_string(color[i], strlen(color[i]), info.row, info.col, 0, MODE_UPDATE_CURSOR, attrib);
	}
	
	puts("\r\n");
}

void dump_svga_mode_list(uint32 far_pointer)
{
	uint16 es = far_pointer >> 16;
	uint16 val = 0;
	do {
	asm(
		"mov %%ds, %%ax\n"	// make sure that %es == %ds by default
		"mov %%ax, %%es\n"
		"mov %1, %%ax\n"	// if it is a far pointer
		"cmp $0, %%ax\n"	// in other words, the val es (%0) is not 0
		"je 1f\n"
		"mov %%ax, %%es\n"	// we push it into %es
		"1:\n"
		"mov %2, %%bx\n"
		"mov %%es:(%%bx), %%ax\n"
		"mov %%ax, %0\n"
		:"=m"(val)
		:"g"(es), "g"(far_pointer)
		:"%ax", "%bx", "cc"
	);
		dumpword(val); puts(" ");
		far_pointer += 2;
	} while(val != 0xFFFF);
	
	puts("\r\n");
}

void show_svga_info()
{
#define IS_VBE2(sig) (sig[0] == 'V' && sig[1] == 'B' && sig[2] == 'E' && sig[3] == '2')

	struct svga_info svga = {0};
	int ret = 0;
	if (ret = get_svga_info(&svga)) {
		puts("get_svga_info failed, return val is ");
		dumpbyte(ret);
		puts("\r\n");
		return;
	}
	
	puts("The SVGA Info \r\n");

#define show_sig(sig)			putc(sig[0]); putc(sig[1]); putc(sig[2]); putc(sig[3]); puts("\r\n");
#define show_string(name, val)	puts(name); puts(val); puts("\r\n");
#define show_word(name, val)	puts(name); dumpword(val); puts("\r\n");
#define show_dword(name, val)	puts(name); dumpdword(val); puts("\r\n");

	puts("signature: "); show_sig(svga.signature);
	show_word("VESA version: ", svga.vesa_ver);
	show_string("OEM name: ", svga.oem);
	show_dword("capabilities flag: ", svga.capability);
	puts("supported VESA & OEM video modes: \r\n");
	dump_svga_mode_list(svga.support_vesa_oem_modes);
	show_word("video memory in 64K blocks: ", svga.mem_size);
if (IS_VBE2(svga.signature)) {
	show_string("OEM software version: ", svga.oem_ver);
	show_string("vendor name: ", svga.vendor_name);
	show_string("product name: ", svga.product_name);
	show_string("product revision: ", svga.product_rev);
	show_string("OEM scratchpad: ", svga.oem_scratchpad);
}

#undef show_sig
#undef show_string	
#undef show_word	
#undef show_dword

	puts("\r\n");
}

void idle_wait()
{
	struct cursor_info info = {0};
	get_cursor_info(0, &info);

	delay(500);
	set_cursor_shape(info.start, info.end, SHAPE_NORMAL);
	delay(500);
	set_cursor_shape(info.start, info.end, SHAPE_INVISIBLE);
}

void my_os(void)
{
	puts("hello world!\r\n\r\n");
	
	color_test();
	
	show_svga_info();
	
	for(;;) idle_wait();
}
