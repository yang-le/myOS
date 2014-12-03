void char_init(void)
{
asm(
	"mov $0xb800, %ax\n"
	"mov %ax, %es\n"
	"xor %di, %di\n"
);	
}

void putc(const char c)
{
asm(
	"movb %0, %%es:(%%di)\n"
	"add $2, %%di\n"
	::"a"(c)
);
}
