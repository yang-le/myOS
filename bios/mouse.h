#ifndef __MOUSE_H__
#define __MOUSE_H__

#include <bios.h>

#define SUCCESS 0
#define ERR_FUNC 1
#define ERR_INPUT 2
#define ERR_INTERFACE 3
#define ERR_NEED_RESEND 4
#define ERR_NO_HANDLER 5

// C200. SYSTEM - POINTING DEVICE BIOS INTERFACE (PS) - ENABLE/DISABLE
int set_mouse_state(uint8 state);

// C201. SYSTEM - POINTING DEVICE BIOS INTERFACE (PS) - RESET


// C205. SYSTEM - POINTING DEVICE BIOS INTERFACE (PS) - INITIALIZE
inline int init_mouse(uint8 data_pack_size);

// C207. SYSTEM - POINTING DEVICE BIOS INTERFACE (PS) - SET DEVICE HANDLER ADDR
inline int set_mouse_handler(far_ptr handler);

#endif
