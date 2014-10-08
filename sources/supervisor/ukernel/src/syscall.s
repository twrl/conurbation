[BITS 64]

[SECTION .text]

_syscall_ep:
    push rcx
    mov rcx, r10
    
    sysret