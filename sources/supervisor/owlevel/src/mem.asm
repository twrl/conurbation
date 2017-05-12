[BITS 64]

[SECTION .text]

; memcpy(void* dest rdi, void* src rsi, size_t count rdx) -> void*
;[SECTION .text.memcpy]
[GLOBAL memcpy];:function (memcpy.end - memcpy)]
memcpy:
        mov rax, rdi
        mov rcx, rdx
        cld
        rep movsb
        ret
    .end:

; memmove(void* dest rdi, void* src rsi, size_t count rdx) -> void*
;[SECTION .text.memmove]
[GLOBAL memmove];:function (memmove.end - memmove)]
memmove:
        mov rax, rdi
        mov rcx, rdx
        cmp rdi, rsi
        jl .rev_move
    .fwd_move:
        cld
        rep movsb
        jmp .done_move
    .rev_move:
        add rsi, rcx
        add rdi, rcx
        std
        rep movsb
    .done_move:
        cld
        ret
    .end:

; memset(void* dest rdi, char value rsi, size_t count rdx) -> void*
;[SECTION .text.memset]
[GLOBAL memset];:function (memset.end - memset)]
memset:
        mov rcx, rdx
        mov rdx, rdi
        mov rax, rsi
        cld
        rep stosb
        mov rax, rdx
        ret
    .end:
