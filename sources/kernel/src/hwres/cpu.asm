[BITS 64]

[GLOBAL get_cpuid:function get_cpuid.end - get_cpuid]
; auto get_cpuid(uint32_t leaf, uint32_t subleaf, uint32_t[4] returns)
get_cpuid:
        push rbx
        mov r10, rdx
        mov rax, rdi
        mov rcx, rsi
        cpuid
        mov [r10], eax
        mov [r10+4], ebx
        mov [r10+8], ecx
        mov [r10+12], edx
        pop rbx
        ret
    .end:

[GLOBAL switch_gdt64:function switch_gdt64.end - switch_gdt64]
switch_gdt64:
        lgdt [GDT64.Pointer]
        push qword GDT64.Code
        push qword .preret
        iretq
    .preret:
        ret
    .end:




[SECTION .rodata]
[GLOBAL GDT64:data GDT64.End - GDT64]
GDT64:                           ; Global Descriptor Table (64-bit).
    .Null: equ $ - GDT64         ; The null descriptor.
    dw 0                         ; Limit (low).
    dw 0                         ; Base (low).
    db 0                         ; Base (middle)
    db 0                         ; Access.
    db 0                         ; Granularity.
    db 0                         ; Base (high).
    .Code: equ $ - GDT64         ; The code descriptor.
    dw 0                         ; Limit (low).
    dw 0                         ; Base (low).
    db 0                         ; Base (middle)
    db 10011010b                 ; Access (exec/read).
    db 00100000b                 ; Granularity.
    db 0                         ; Base (high).
    .Data: equ $ - GDT64         ; The data descriptor.
    dw 0                         ; Limit (low).
    dw 0                         ; Base (low).
    db 0                         ; Base (middle)
    db 10010010b                 ; Access (read/write).
    db 00000000b                 ; Granularity.
    db 0                         ; Base (high).
    .Pointer:                    ; The GDT-pointer.
    dw $ - GDT64 - 1             ; Limit.
    dq GDT64                     ; Base.
    .End:
