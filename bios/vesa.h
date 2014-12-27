#ifndef __VESA_H__
#define __VESA_H__

#include <bios.h>

// 4F00. VESA SuperVGA BIOS (VBE) - GET SuperVGA INFORMATION
struct __PACKED__ svga_info {
	char 	signature[4];
	uint16	vesa_ver;
	char*	oem;
	uint32	capability;
	uint32	support_vesa_oem_modes;
	uint16	mem_size;
	union __PACKED__ {
		struct __PACKED__ svga_info_vbe_v1 {
			uint8 _reserved[236];
		} v1;
		struct __PACKED__ svga_info_vbe_v2 {
			uint16	oem_ver;
			char*	vendor_name;
			char*	product_name;
			char*	product_rev;
			uint16	vbe_af_ver;
			uint32	support_accelerate_modes;
			uint8	_reserved[216];
		} v2;
	};
	char	oem_scratchpad[256];
};

int get_svga_info(struct svga_info* info);

// 4F01. VESA SuperVGA BIOS - GET SuperVGA MODE INFORMATION
struct __PACKED__ svga_mode_info {
	union __PACKED__ {
		uint16 	all;
		struct __PACKED__ {
			uint16 supported : 1;
			uint16 opt_info : 1;
			uint16 bios_output : 1;
			uint16 color : 1;
			uint16 graphics : 1;
			uint16 reserved : 11;
		};
	} mode_attrib;
	union __PACKED__ {
		uint8 	all;
		struct __PACKED__ {
			uint8 valid : 1;
			uint8 readable : 1;
			uint8 writable : 1;
			uint8 reserved : 5;
		};		
	} win_A_attrib, win_B_attrib;
	uint16	win_granularity;	// in KB
	uint16	win_size;			// in KB
	uint16	win_A_start_seg;
	uint16	win_B_start_seg;
	void*	win_pos_func;
	uint16	bytes_per_scanline;
	uint16	width;				// in pixels (graphics) or characters (text)
	uint16	height;				// in pixels (graphics) or characters (text)
	uint8	char_cell_width;	// in pixels
	uint8	char_cell_height;	// in pixels
	uint8	num_mem_planes;
	uint8	bits_per_pixel;
	uint8	num_banks;
	uint8	mem_model_type;
	uint8	size_of_bank;		// in KB
	uint8	num_image_pages;
	uint8	reserved;
	struct __PACKED__ svga_mode_info_vbe_v1 {
		uint8	red_mask_size;
		uint8	red_field_pos;
		uint8	green_mask_size;
		uint8	green_field_pos;
		uint8	blue_mask_size;
		uint8	blue_field_pos;
		uint8	reserved_mask_size;
		uint8	reserved_mask_pos;
		uint8	direct_color_mode;
	} v1;
	struct __PACKED__ svga_mode_info_vbe_v2 {
		void*	linear_video_buff;
		void*	offscreen_mem;
		uint16	offscreen_mem_size;	// in KB
	} v2;
	struct __PACKED__ svga_mode_info_vbe_v3 {
		uint16	bytes_per_scanline;
		uint8	num_image_pages_banked;
		uint8	num_image_pages_linear;
		uint8	red_mask_size;
		uint8	red_field_pos;
		uint8	green_mask_size;
		uint8	green_field_pos;
		uint8	blue_mask_size;
		uint8	blue_field_pos;
		uint8	reserved_mask_size;
		uint8	reserved_mask_pos;
		uint32	max_pixel_clock;	// in Hz
	} v3;
	uint8 _reserved[190];
};

int get_svga_mode_info(uint16 mode, struct svga_mode_info* info);

// 4F02. VESA SuperVGA BIOS - SET SuperVGA VIDEO MODE
int set_svga_mode(uint16 mode, bool cls /* TODO: struct crtc_info* info*/);

#endif