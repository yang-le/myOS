#include <bios.h>
#include <char.h>

void my_os(void)
{
	char str[] = "hello world!\r\n\r\n";
	puts(str);
	
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

	for(;;){
		delay(500);
		set_cursor_shape(info.start, info.end, 0);
		delay(500);
		set_cursor_shape(info.start, info.end, 1);
	}
}
