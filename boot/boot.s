BOOTSEG		= 0x07C0		/* original address of boot-sector */
VIDEO		= 0xB800

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

# init disp
movw $VIDEO, %ax
movw %ax, %es
xorw %di, %di

#movb %ds:newWorld, %al
#call DispAL

movb $'c', %es:(%di)
addw $2, %di

#jmp newWorld
call _my_os

movb $'b', %es:(%di)
addw $2, %di

call _foo_ret

movb $'a', %es:(%di)
addw $2, %di

hlt:
jmp hlt

.org 510
bootflag:
.word 0xAA55
newWorld:
