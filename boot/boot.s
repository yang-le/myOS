BOOTSEG		= 0x07C0		/* original address of boot-sector */

.code16
.global bootsect_start

bootsect_start:

# Normalize the start address
ljmp	$BOOTSEG, $start

start:
movw	%cs, %ax
movw	%ax, %ds
movw	%ax, %es
movw	%ax, %ss
xorw	%sp, %sp
sti
cld

# read 2nd sector
movw $0x200, %bx
movb $1, %al
movb $2, %ah
movw $2, %cx
movw $0, %dx
int $0x13

# Force %es = %ds
movw	%ds, %ax
movw	%ax, %es
cld

# We will have entered with %cs = %ds+0x20, normalize %cs so
# it is on par with the other segments.
pushw	%ds
pushw	$6f
lretw
6:

#jmp newWorld
calll _my_os

die:
hlt
jmp die

.org 510
bootflag:
.word 0xAA55
