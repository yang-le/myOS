
inline void set_cursor_shape(unsigned char start, unsigned char end, unsigned char options)
{
unsigned short cx = ((start & 0x0F) << 8) | (end & 0x0F) | ((options & 0x03) << 13);
asm(
	"mov $0x01, %%ah\n"
	"mov %0, %%cx\n"
	"int $0x10\n"
	::"g"(cx)
	:"%ah", "%cx"
);
}

inline void tele_char(unsigned char c, unsigned char page, unsigned char color)
{
asm(
	"mov $0x0E, %%ah\n"
	"mov %0, %%al\n"
	"mov %1, %%bh\n"
	"mov %2, %%bl\n"
	"int $0x10\n"
	::"g"(c), "g"(page), "g"(color)
	:"%ax", "bx"
);
}

inline void tele_string()
{

}

