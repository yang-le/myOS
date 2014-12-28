#ifndef __BIOS_H__
#define __BIOS_H__

#include <types.h>
#include "bios/video.h"
#include "bios/vesa.h"
#include "bios/misc.h"

enum bios_calls {
	bc_video_service = 0x10,
	bc_device_list,
	bc_memory_size,
	bc_disk_service,
	bc_serial_service,
	bc_misc_service,
	bc_keyboard,
	bc_print_service,
	bc_rtc_service = 0x1A
};

#endif