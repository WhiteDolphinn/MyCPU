in
pop ax
push 1
pop bx

call :fact

push bx
out
hlt

:fact
push 0
push ax
je :ex_fact

push ax
push bx
mul
pop bx

push ax
push 1
sub
pop ax
call :fact

:ex_fact
ret
