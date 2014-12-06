
void set_cursor_shape(unsigned char start, unsigned char end, unsigned char options)
{
unsigned short cx = ((start & 0x0F) << 8) | (end & 0x0F) | ((options & 0x03) << 13);
asm(
	"mov $0x01, %%ah\n"
	"mov %0, %%cx\n"
	"int $0x10\n"
	::"r"(cx)
	:"%ah", "%cx"
);
}
