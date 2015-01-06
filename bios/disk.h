#ifndef __DISK_H__
#define __DISK_H__

#include <bios.h>

// 02. DISK - READ SECTOR(S) INTO MEMORY
uint8 _read_sector(uint8 driver, uint8 head, uint8 track, uint8 sector, uint8 num, far_ptr buff);

// 03. DISK - WRITE DISK SECTOR(S)
uint8 _write_sector(uint8 driver, uint8 head, uint8 track, uint8 sector, uint8 num, far_ptr buff);

#endif
