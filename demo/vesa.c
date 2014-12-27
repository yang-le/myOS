#include <bios.h>
#include <char.h>
#include "vesa.h"

#define show_sig(sig)			putc(sig[0]); putc(sig[1]); putc(sig[2]); putc(sig[3]); puts("\r\n");
#define show_string(name, val)	puts(name); puts(val); puts("\r\n");
#define show_byte(name, val)	puts(name); dumpbyte(val); puts("\r\n");
#define show_word(name, val)	puts(name); dumpword(val); puts("\r\n");
#define show_dword(name, val)	puts(name); dumpdword(val); puts("\r\n");

#define show_win_attrib(name, attr) \
	puts(name); dumpbyte(attr.all); putc(' '); \
	putc(attr.valid ? 'O' : 'X');	\
	putc(attr.readable ? 'R' : ' ');	\
	putc(attr.writable ? 'W' : ' ');	\
	puts("\r\n");

#define show_mode_atrrib(name, attr) \
	puts(name); dumpword(attr.all); putc(' '); \
	puts(attr.supported ? "O " : "X ");	\
	puts(attr.opt_info ? "opt_o " : "opt_x ");	\
	puts(attr.bios_output ? "bios_o " : "bios_x ");	\
	puts(attr.color ? "color " : "mono ");	\
	puts(attr.graphics ? "graph " : "text ");	\
	puts("\r\n");

void dump_svga_mode(uint16 mode, uint8 ver)
{
	struct svga_mode_info info= {0};
	get_svga_mode_info(mode, &info);
	show_mode_atrrib("mode_attrib: ", info.mode_attrib);
	show_win_attrib("win_A_attrib: ", info.win_A_attrib);
	show_win_attrib("win_B_attrib: ", info.win_B_attrib);
	show_word("win_granularity: ", info.win_granularity);	
	show_word("win_size: ", info.win_size);			
	show_word("win_A_start_seg: ", info.win_A_start_seg);
	show_word("win_B_start_seg: ", info.win_B_start_seg);
	show_word("win_pos_func: ", info.win_pos_func);
	show_word("bytes_per_scanline: ", info.bytes_per_scanline);
	show_word("width: ", info.width);				
	show_word("height: ", info.height);				
	show_byte("char_cell_width: ", info.char_cell_width);	
	show_byte("char_cell_height: ", info.char_cell_height);	
	show_byte("num_mem_planes: ", info.num_mem_planes);
	show_byte("bits_per_pixel: ", info.bits_per_pixel);
	show_byte("num_banks: ", info.num_banks);
	show_byte("mem_model_type: ", info.mem_model_type);
	show_byte("size_of_bank: ", info.size_of_bank);		
	show_byte("num_image_pages: ", info.num_image_pages);
	
	puts("\r\n");
}

void dump_svga_mode_list(uint32 far_pointer, uint8 ver)
{
	uint16 es = far_pointer >> 16;
	uint16 val = 0;
	
	for(;;) {
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
		far_pointer += 2;
		if (val == 0xFFFF) break;
		dumpword(val); puts(" "); //dump_svga_mode(val, ver);
	};
	
	puts("\r\n");
}

void show_svga_info()
{
	struct svga_info svga = {0};
	int ret = 0;
	if (ret = get_svga_info(&svga)) {
		puts("get_svga_info failed, return val is ");
		dumpbyte(ret);
		puts("\r\n");
		return;
	}
	
	puts("The SVGA Info \r\n");

	puts("signature: "); show_sig(svga.signature);
	show_word("VESA version: ", svga.vesa_ver);
	show_string("OEM name: ", svga.oem);
	show_dword("capabilities flag: ", svga.capability);
	puts("supported VESA & OEM video modes: \r\n");
	dump_svga_mode_list(svga.support_vesa_oem_modes, IS_VBE2(svga.signature) ? 2 : 1);
	show_word("video memory in 64K blocks: ", svga.mem_size);
if (IS_VBE2(svga.signature)) {
	show_word("OEM software version: ", svga.v2.oem_ver);
	show_string("vendor name: ", svga.v2.vendor_name);
	show_string("product name: ", svga.v2.product_name);
	show_string("product revision: ", svga.v2.product_rev);
if (IS_STEREOSCOPIC_SUPPORT(svga.capability)) {
	show_word("VBE/AF version: ", svga.v2.vbe_af_ver);
	puts("supported accelerated video modes: \r\n");
	dump_svga_mode_list(svga.v2.support_accelerate_modes, 2);
}
}
	show_string("OEM scratchpad: ", svga.oem_scratchpad);

	puts("\r\n");
}
