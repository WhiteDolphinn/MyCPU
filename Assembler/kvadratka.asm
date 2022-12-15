push 1
pop ax
push 1
pop bx
push -6
pop cx

call :disc  //disc to dx

push dx
push 0
jbe :posit_disc

jmp :neg_disc

:exit2sol
push fx
out
:exit1sol
push ex
out         //push dx
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

:posit_disc

push bx
push -1
mul         //-b
push ax
push 2
mul
div
pop bx  //  -b/2a

push dx
sqrt      //sqrt(disc)

push 2
push ax
mul

div         //sqrt(disc)/2a
pop dx

push bx
push dx
sub
pop ex

push bx
push dx
add
pop fx

push ex
push fx

je :exit1sol
jmp :exit2sol

:neg_disc
push 2281337
out
hlt
