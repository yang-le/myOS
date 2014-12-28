#include "vesa.h"

#define CHECK_AND_RETURN(ret) {		\
	if ((ret & 0xFF) == 0x4F) {		\
		return ret >> 8;			\
	} else {						\
		return 2;					\
	}								\
}

// 4F00. VESA SuperVGA BIOS (VBE) - GET SuperVGA INFORMATION
inline int get_svga_info(struct svga_info* info)
{
	uint16 ret = 0;
asm(
	"mov $0x4F00, %%ax\n"
	"mov %1, %%di\n"
	"int $0x10\n"
	"mov %%ax, %0"
	:"=m"(ret)
	:"g"(info)
	:"%ax", "%di", "memory"
);
	CHECK_AND_RETURN(ret);
}

// 4F01. VESA SuperVGA BIOS - GET SuperVGA MODE INFORMATION
inline int get_svga_mode_info(uint16 mode, struct svga_mode_info* info)
{
	uint16 ret = 0;
asm(
	"mov $0x4F01, %%ax\n"
	"mov %1, %%di\n"
	"mov %2, %%cx\n"
	"int $0x10\n"
	"mov %%ax, %0"
	:"=m"(ret)
	:"g"(info), "g"(mode)
	:"%ax", "%di", "%cx", "memory"
);
	CHECK_AND_RETURN(ret);
}

// 4F02. VESA SuperVGA BIOS - SET SuperVGA VIDEO MODE
inline int set_svga_mode(uint16 mode, bool cls /* TODO: struct crtc_info* info*/)
{
	uint16 ret = 0;
	if (!cls) mode |= 1 << 15;	
asm(
	"mov $0x4F02, %%ax\n"
	"mov %1, %%bx\n"
	"int $0x10\n"
	"mov %%ax, %0"
	:"=m"(ret)
	:"g"(mode)
	:"%ax", "%bx", "memory"
);
	CHECK_AND_RETURN(ret);
}

// 4F05. VESA SuperVGA BIOS - CPU VIDEO MEMORY CONTROL
inline int set_svga_mem_window(uint8 win_num, uint8 page_addr)
{
	uint16 ret = 0;
asm(
	"mov $0x4F05, %%ax\n"
	"mov $0, %%bh\n"
	"mov %1, %%bl\n"
	"mov %2, %%dx\n"
	"int $0x10\n"
	"mov %%ax, %0"
	:"=m"(ret)
	:"g"(win_num), "g"(page_addr)
	:"%ax", "%bx", "%dx", "memory"
);
	CHECK_AND_RETURN(ret);
}
