push 5
pop ax
push 2
pop bx
call :lin_solve
push cx
out
hlt

:lin_solve
push ax
push bx
push -1
mul
div
pop cx
ret

