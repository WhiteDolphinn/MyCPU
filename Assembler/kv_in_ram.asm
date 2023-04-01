in   //push 1
pop [0]
in      //push 2
pop [1]
in      //push 1
pop [2]

call :disc  //disc to dx

push [3]
push 0
je :null_disc

push [3]
push 0
jbe :posit_disc
jmp :neg_disc

:exit888sol
push 888
out
hlt

:exit2sol
push [5]
out

:exit1sol
push [4]
out         //push dx
hlt

:lin_solve
push [0]
push [0]
mul
push [1]
push [1]
mul
add
push 0
je :exit888sol

push [0]
push [1]
push -1
mul
div
pop [4]
ret

:disc
push [1]
push [1]
mul
push 4
push [0]
push [2]
mul
mul
sub
pop [3]
ret

:posit_disc

push [1]
push -1
mul         //-b
push [0]
push 2
mul
div
pop [1]  //  -b/2a

push [3]
sqrt      //sqrt(disc)

push 2
push [0]
mul

div         //sqrt(disc)/2a
pop [3]

push [1]
push [3]
sub
pop [4]

push [1]
push [3]
add
pop [5]

push [4]
push [5]

je :exit1sol
jmp :exit2sol

:neg_disc
push 2281337
out
hlt

:null_disc
push 2
push [0]
mul
pop [0]

call :lin_solve
jmp :exit1sol

