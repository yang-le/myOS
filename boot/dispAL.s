DispAL:
movw $VIDEO, %dx
movw %dx, %es
movb %al, %ah
shrb $4, %al
call doDispAL
movb %ah, %al
call doDispAL
ret

doDispAL:
andb $0x0f, %al
cmpb $10, %al
jb num
addb $'A' - 10, %al
jmp disp

num:
addb $'0', %al

disp:
movb %al, %es:(%di)
addw $2, %di

ret