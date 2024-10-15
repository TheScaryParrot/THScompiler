section .text
Hello:
mov rbp, rsp
sub rsp, 1
mov dl, byte [rbp+16]
mov byte [rbp-1], dl
sub rsp, 1
mov dl, byte [rbp+17]
mov byte [rbp-2], dl
mov rsp, rbp
mov al, byte [rbp-1]
and al, byte [rbp-2]
mov byte [rbp-1], al
mov rax, rbp
sub rax, 1
ret 
add rsp, 2
Hello2:
mov rbp, rsp
sub rsp, 4
mov edx, dword [rbp+16]
mov dword [rbp-4], edx
sub rsp, 4
mov edx, dword [rbp+20]
mov dword [rbp-8], edx
mov rsp, rbp
mov eax, dword [rbp-4]
add eax, dword [rbp-8]
mov dword [rbp-4], eax
mov rax, rbp
sub rax, 4
ret 
add rsp, 8
extern _print
global _start
_start:
mov rbp, rsp
extern mod
sub rsp, 4
mov edx, 66
mov dword [rbp-4], edx
sub rsp, 4
mov edx, 2
mov dword [rbp-8], edx
sub rsp, 9
mov edx, 2
mov dword [rbp-17], edx
mov dl, byte [bool1]
mov byte [rbp-21], dl
mov edx, __float32__(2.000000)
mov dword [rbp-22], edx
sub rsp, 9
mov edx, dword [rbp-17]
mov dword [rbp-26], edx
mov dl, byte [rbp-21]
mov byte [rbp-30], dl
mov edx, dword [rbp-22]
mov dword [rbp-31], edx
sub rsp, 4
sub rsp, 4
mov edx, 70
mov dword [rbp-34], edx
sub rsp, 4
mov edx, 4
mov dword [rbp-38], edx
push rbp
call _print
pop rbp
add rsp, 8
jmp JL1 
JL2:
sub rsp, 4
mov edx, 71
mov dword [rbp-34], edx
sub rsp, 4
mov edx, 4
mov dword [rbp-38], edx
push rbp
call _print
pop rbp
add rsp, 8
JL1:
jmp JL4 
sub rsp, 4
mov edx, 71
mov dword [rbp-34], edx
sub rsp, 4
mov edx, 4
mov dword [rbp-38], edx
push rbp
call _print
pop rbp
add rsp, 8
jmp JL3 
JL4:
sub rsp, 4
mov edx, 70
mov dword [rbp-34], edx
sub rsp, 4
mov edx, 4
mov dword [rbp-38], edx
push rbp
call _print
pop rbp
add rsp, 8
JL3:
mov edx, dword [rbp-8]
cmp edx, [rbp-4]
jne JL6 
sub rsp, 4
mov edx, 66
mov dword [rbp-34], edx
sub rsp, 4
mov edx, 4
mov dword [rbp-38], edx
push rbp
call _print
pop rbp
add rsp, 8
jmp JL5 
JL6:
mov edx, dword [rbp-8]
cmp edx, [rbp-4]
jge JL7 
sub rsp, 4
mov edx, 67
mov dword [rbp-34], edx
sub rsp, 4
mov edx, 4
mov dword [rbp-38], edx
push rbp
call _print
pop rbp
add rsp, 8
jmp JL5 
JL7:
sub rsp, 4
mov edx, 68
mov dword [rbp-34], edx
sub rsp, 4
mov edx, 4
mov dword [rbp-38], edx
push rbp
call _print
pop rbp
add rsp, 8
JL5:
sub rsp, 4
mov edx, 10
mov dword [rbp-34], edx
JL9:
mov edx, dword [rbp-34]
cmp edx, 0
jle JL8 
mov edx, 1
sub dword [rbp-34], edx
jmp JL9 
JL8:
sub rsp, 4
mov edx, __float32__(3.000000)
mov dword [rbp-38], edx
sub rsp, 4
mov edx, 0
mov dword [rbp-42], edx
JL12:
mov edx, dword [rbp-42]
cmp edx, 10
jge JL10 
mov edx, __float32__(1.000000)
add dword [rbp-38], edx
JL11:
mov edx, 2
add dword [rbp-42], edx
jmp JL12 
JL10:
add rsp, 4
sub rsp, 4
mov edx, dword [rbp-31]
mov dword [rbp-42], edx
sub rsp, 4
mov edx, 1000
mov dword [rbp-46], edx
sub rsp, 4
mov edx, dword [rbp-4]
mov dword [rbp-50], edx
push rbp
call mod
pop rbp
add rsp, 8
sub rsp, 4
mov edx, dword [rax]
mov dword [rbp-46], edx
mov edx, dword [rbp-46]
mov dword [rbp-4], edx
sub rsp, 4
mov edx, dword [rbp-4]
mov dword [rbp-50], edx
sub rsp, 4
mov edx, 4
mov dword [rbp-54], edx
push rbp
call _print
pop rbp
add rsp, 8
sub rsp, 4
mov edx, dword [rbp-4]
mov dword [rbp-50], edx
sub rsp, 4
mov edx, 2
mov dword [rbp-54], edx
push rbp
call Hello2
pop rbp
add rsp, 8
sub rsp, 4
mov edx, dword [rax]
mov dword [rbp-50], edx
sub rsp, 4
mov edx, dword [rbp-50]
mov dword [rbp-54], edx
sub rsp, 4
mov edx, 4
mov dword [rbp-58], edx
push rbp
call _print
pop rbp
add rsp, 12
sub rsp, 4
mov edx, 3
mov dword [rbp-50], edx
sub rsp, 4
mov edx, 2
mov dword [rbp-54], edx
sub rsp, 4
mov edx, 2
mov dword [rbp-58], edx
mov eax, dword [rbp-50]
mov edx, 5
mul edx
sub rsp, 4
mov dword [rbp-62], eax
mov eax, dword [rbp-54]
shl eax, 1
sub eax, 4
mov edx, eax
mov eax, dword [rbp-62]
add eax, edx
sub rsp, 4
mov dword [rbp-66], eax
mov eax, dword [rbp-58]
add eax, 1
mov edx, eax
mov eax, 1
mul edx
mov edx, dword [rbp-54]
mul edx
shr eax, 1
mov edx, eax
mov eax, dword [rbp-66]
sub eax, edx
sub rsp, 4
mov dword [rbp-70], eax
mov edx, 53
add dword [rbp-70], edx
sub rsp, 4
mov edx, dword [rbp-70]
mov dword [rbp-74], edx
sub rsp, 4
mov edx, 4
mov dword [rbp-78], edx
push rbp
call _print
pop rbp
add rsp, 8
sub rsp, 4
mov edx, 150
mov dword [rbp-74], edx
mov eax, dword [rbp-74]
xor rdx, rdx
mov ebx, 80
div ebx
mov eax, edx
sub rsp, 4
mov dword [rbp-78], eax
sub rsp, 4
mov edx, 4
mov dword [rbp-82], edx
push rbp
call _print
pop rbp
add rsp, 8
add rsp, 74
mov eax, 60
xor edi, edi
syscall 
section .bss
bool3: resb 1
float3: resb 4
section .data
bool2: db 0
section .rodata
bool1: db 1
float2: dd 1.714286
