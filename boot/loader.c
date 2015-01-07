#include <bios.h>
#include "boot.h"

#define SECTORS_PER_TRACK 18
// SED FIXME START
#define SYS_SIZE_IN_SECTOR 0
// SED FIXME END

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

uint8 read_sector(uint8 driver, uint8 cylinder, uint8 head, uint8 sector, uint8 num, far_ptr buff)
{
	uint8 ret = 0;
	while(num--) {
		if (ret = _read_sector(driver, cylinder, head, sector, 1, buff))
			return ret;

		buff += 512;
		if (++sector > SECTORS_PER_TRACK) {
			if (++head >= 2) {
				++cylinder;
				head = 0;
			}
			sector = 1;
		}
	}
	return ret;
}

void load_system()
{
	if (read_sector(0, 0, 0,
		1 + BOOT_SIZE_IN_SECTOR + LOADER_SIZE_IN_SECTOR,
		SYS_SIZE_IN_SECTOR, ADDR_OF_NEW_WORLD))
	{
		for(;;);
	}
	my_os();
}

// make sure loader end at sector boundary
asm(".org "STR(LOADER_SIZE_IN_SECTOR)" * 512");
