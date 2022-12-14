push 1
pop ax
push 1
pop bx
push -6
pop cx

call :disc
push dx
out
hlt

:lin_solve
push ax
push bx
push -1
mul
div
pop ex
ret

:disc
push bx
push bx
mul

push 4
push ax
push cx
mul
mul

sub
pop dx
ret

