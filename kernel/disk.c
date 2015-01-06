#include <bios.h>

#define TRACKS_PER_HEAD 80
#define SECTORS_PER_TRACK 18

uint8 read_sector(uint8 driver, uint8 head, uint8 track, uint8 sector, uint8 num, far_ptr buff)
{
	uint8 ret = 0;
	while(num--) {
		if (ret = _read_sector(driver, head, track, sector, 1, buff))
			return ret;

		buff += 512;
		if (++sector > SECTORS_PER_TRACK) {
			if (++head >= 2) {
				++track;
				head = 0;
			}
			sector = 1;
		}
	}
	return ret;
}

uint8 write_sector(uint8 driver, uint8 head, uint8 track, uint8 sector, uint8 num, far_ptr buff)
{
	uint8 ret = 0;
	while(num--) {
		if (ret = _write_sector(driver, head, track, sector, 1, buff))
			return ret;

		buff += 512;
		if (++sector > SECTORS_PER_TRACK) {
			if (++head >= 2) {
				++track;
				head = 0;
			}
			sector = 1;
		}
	}
	return ret;
}
