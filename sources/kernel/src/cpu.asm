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

    
