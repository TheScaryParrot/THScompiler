global _print

; void print(int length, int char)
_print:
mov rbp, rsp

; first argument arp+16 is int32 of length
; second argument rbp+20 is first char, next char is at rbp+21 and so on

; print
mov rax, 1
mov rdi, 1
mov rsi, rbp
add rsi, 20
xor rdx, rdx ; clear rdx
mov edx, dword [rbp+16] ; mov length to rdx (edx is in lower 32 bits of rdx)
syscall

mov rsp, rbp
ret

