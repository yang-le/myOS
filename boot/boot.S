#include "boot.h"

.code16
.global bootsect_start

bootsect_start:

// Normalize the start address
ljmp	$BOOTSEG, $start

start:
movw	%cs, %ax
movw	%ax, %ds
movw	%ax, %es
movw	%ax, %ss
xorw	%sp, %sp
sti
cld

// read loader
movw $0x200, %bx
movb $LOADER_SIZE_IN_SECTOR, %al
movb $2, %ah
movw $2, %cx
movw $0, %dx
int $0x13

// Force %es = %ds
movw	%ds, %ax
movw	%ax, %es
cld

// We will have entered with %cs = %ds+0x20, normalize %cs so
// it is on par with the other segments.
pushw	%ds
pushw	$6f
lretw
6:

// call loader
calll _load_system

die:
hlt
jmp die

.org 510
bootflag:
.word 0xAA55
