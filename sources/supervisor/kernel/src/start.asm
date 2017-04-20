[BITS 64]

[EXTERN _GLOBAL_OFFSET_TABLE_]

[EXTERN __preinit_array_start]
[EXTERN __preinit_array_end]
[EXTERN __init_array_start]
[EXTERN __init_array_end]
[EXTERN __fini_array_start]
[EXTERN __fini_array_end]

[EXTERN kernel_main]
;[EXTERN __cxa_finalize]

[SECTION .text.startup]

[GLOBAL _start:function (_start.end - _start)]
_start:
        sub rsp, 32

        mov [_uefi_image_handle wrt ..sym], rcx
        mov [_uefi_system_table_ptr wrt ..sym], rdx

        mov rdi, [__preinit_array_start wrt ..sym]
        mov rsi, [__preinit_array_end wrt ..sym]
        call fun_array_preinit

        mov rdi, [__init_array_start wrt ..sym]
        mov rsi, [__init_array_end wrt ..sym]
        call fun_array_preinit

        mov rdi, [_uefi_image_handle wrt ..sym]
        mov rsi, [_uefi_system_table_ptr wrt ..sym]

        call kernel_main

        push rax

        mov rdi, [__fini_array_start wrt ..sym]
        mov rsi, [__fini_array_end wrt ..sym]
        call fun_array_rev

;        xor rdi, rdi
;        call __cxa_finalize

        pop rax

        add rsp, 32
        ret
    .end:

fun_array_preinit:
        push r12
        push r13
        push r15

        mov r12, rdi
        mov r13, rsi
    .begin_loop:
        cmp r12, r13
        je .end_loop
        mov r15, [r12]
        mov rdi, [_uefi_image_handle]
        mov rsi, [_uefi_system_table_ptr]
        call r15
        add r12, 8
        jmp .begin_loop
    .end_loop:
        pop r15
        pop r13
        pop r12
        ret
    .end:

fun_array_fwd:
        push r12
        push r13
        push r15

        mov r12, rdi
        mov r13, rsi
    .begin_loop:
        cmp r12, r13
        je .end_loop
        mov r15, [r12]
        call r15
        add r12, 8
        jmp .begin_loop
    .end_loop:
        pop r15
        pop r13
        pop r12
        ret
    .end:

fun_array_rev:
        push r12
        push r13
        push r15

        mov r12, rdi
        mov r13, rsi
    .begin_loop:
        cmp r12, r13
        je .end_loop
        sub r13, 8
        mov r15, [r13]
        call r15
        jmp .begin_loop
    .end_loop:
        pop r15
        pop r13
        pop r12
        ret
    .end:

[GLOBAL enable_sse:function (enable_sse.end - enable_sse)]

enable_sse:
        mov rax, cr0
        and ax, 0xFFFB		;clear coprocessor emulation CR0.EM
        or ax, 0x2			;set coprocessor monitoring  CR0.MP
        mov cr0, rax
        mov rax, cr4
        or ax, 3 << 9		;set CR4.OSFXSR and CR4.OSXMMEXCPT at the same time
        mov cr4, rax
        ret
    .end:

[SECTION .preinit_array]

dq enable_sse

;[EXTERN preinit_liballoc]
;dq preinit_liballoc

;[EXTERN preinit_test]
;dq preinit_test

[SECTION .data]

[GLOBAL _uefi_image_handle:data 8]
[GLOBAL _uefi_system_table_ptr:data 8]

_uefi_image_handle: dq 0
_uefi_system_table_ptr: dq 0
