[BITS 64]
[SECTION .text]
;[ALIGN 4]

[GLOBAL _start:function _start.end - _start]
[EXTERN efi_main]
[EXTERN _self_relocate]

_start:
        call _self_relocate
        call efi_main
    .end:

    
[SECTION .data]
dummy: dq 0

[SECTION .reloc]
r0:
        dq (dummy - r0)
        dq 10
        dw 0