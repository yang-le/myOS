
typedef unsigned char uint8_t;

void my_os(void)
{
asm(
	"mov $0xb800, %ax\n"
	"mov %ax, %es\n"
	"xor %di, %di\n"
	"mov $'c', %al\n"
	"mov %al, %es:(%di)\n"
	"add $2, %di\n"
);
for(;;);
}
