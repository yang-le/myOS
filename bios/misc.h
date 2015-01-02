#ifndef __MSIC_H__
#define __MSIC_H__

#include <bios.h>

// 86. BIOS - WAIT (AT,PS)
void delay(uint32 ms);

// C0. SYSTEM - GET CONFIGURATION
int get_sys_config(far_ptr *p);


#include "mouse.h"

#endif
