section .data
    const1 dq 2.000000
    const2 dq 0.000000
    const3 dq 1.000000

section .text
global f1
global f2
global f3
f1:
    push ebp
    mov ebp, esp
    finit
    fld qword[ebp + 8]
    fsin
    fld qword[const1]
    fmulp
    pop ebp
    ret

f2:
    push ebp
    mov ebp, esp
    finit
    fld qword[const2]
    fld qword[ebp + 8]
    fsubp
    pop ebp
    ret

f3:
    push ebp
    mov ebp, esp
    finit
    fld qword[const3]
    fld qword[ebp + 8]
    faddp
    pop ebp
    ret
