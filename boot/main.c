
#define VIDEO 0x000B8000
typedef unsigned char uint8_t;

void my_os(void)
{
	*(uint8_t *)VIDEO = 'x';
	*(uint8_t *)(VIDEO + 2) = 'x';
	*(uint8_t *)(VIDEO + 4) = 'x';
	
	for(;;);
}

void foo_ret(void)
{
	return;
}

void foo_noret(void)
{
	for(;;);
}
