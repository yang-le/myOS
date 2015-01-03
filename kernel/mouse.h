#include <bios.h>

union mouse_status {
	struct {
		uint16 left_button : 1;
		uint16 right_button : 1;
		uint16 middle_button : 1;
		uint16 _reserved : 1;
		uint16 x_negative : 1;
		uint16 y_negative : 1;
		uint16 x_overflow : 1;
		uint16 y_overflow : 1;
		uint16 reserved : 8;
	};
	uint16 val;
};

typedef void (*mouse_callback)(union mouse_status status, uint16 x, uint16 y);

void mouse_init();
void set_mouse_callback(mouse_callback func);
void default_mouse_callback(union mouse_status status, uint16 _x, uint16 _y);
