[BITS 64]

[SECTION .text]

[GLOBAL _syscall_ep:function]
_syscall_ep:
    push rcx
    mov rcx, r10
    
    sysret