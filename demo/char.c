#include <bios.h>
#include <char.h>

void cursor_blink()
{
	struct cursor_info info = {0};
	get_cursor_info(0, &info);

	delay(500);
	set_cursor_shape(info.start, info.end, SHAPE_NORMAL);
	delay(500);
	set_cursor_shape(info.start, info.end, SHAPE_INVISIBLE);
}

void color_char_demo()
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
