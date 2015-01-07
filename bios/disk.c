#include "disk.h"

// 02. DISK - READ SECTOR(S) INTO MEMORY
uint8 _read_sector(uint8 driver, uint8 cylinder, uint8 head, uint8 sector, uint8 num, far_ptr buff)
{
	uint8 ret = 0;
	uint16 es = buff >> 16;
asm(
	"mov %%ds, %%ax\n"	// make sure that %es == %ds by default
	"mov %%ax, %%es\n"
	"mov %1, %%ax\n"	// if s is a far pointer
	"cmp $0, %%ax\n"	// in other words, the val es (%0) is not 0
	"je 1f\n"
	"mov %%ax, %%es\n"	// we push it into %es
	"1:\n"
	"mov $0x02, %%ah\n"	
	"mov %2, %%dl\n"
	"mov %3, %%dh\n"
	"mov %4, %%ch\n"
	"mov %5, %%cl\n"
	"mov %6, %%al\n"
	"mov %7, %%bx\n"
	"int $0x13\n"
	"mov %%ah, %0\n"
	:"=m"(ret)
	:"g"(es), "g"(driver), "g"(head), "g"(cylinder), "g"(sector), "g"(num), "g"(buff)
	:"%ax", "%bx", "%cx", "%dx", "memory", "cc"
);
	return ret;
}

// 03. DISK - WRITE DISK SECTOR(S)
uint8 _write_sector(uint8 driver, uint8 cylinder, uint8 head, uint8 sector, uint8 num, far_ptr buff)
{
	uint8 ret = 0;
	uint16 es = buff >> 16;
asm(
	"mov %%ds, %%ax\n"	// make sure that %es == %ds by default
	"mov %%ax, %%es\n"
	"mov %1, %%ax\n"	// if s is a far pointer
	"cmp $0, %%ax\n"	// in other words, the val es (%0) is not 0
	"je 1f\n"
	"mov %%ax, %%es\n"	// we push it into %es
	"1:\n"
	"mov $0x03, %%ah\n"	
	"mov %2, %%dl\n"
	"mov %3, %%dh\n"
	"mov %4, %%ch\n"
	"mov %5, %%cl\n"
	"mov %6, %%al\n"
	"mov %7, %%bx\n"
	"int $0x13\n"
	"mov %%ah, %0\n"
	:"=m"(ret)
	:"g"(es), "g"(driver), "g"(head), "g"(cylinder), "g"(sector), "g"(num), "g"(buff)
	:"%ax", "%bx", "%cx", "%dx", "memory", "cc"
);
	return ret;	
}
