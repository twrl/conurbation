[BITS 64]

[SECTION .text]
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


[SECTION .note.Conurbation.Boot alloc]

note_c_boot:
        dd .1 - .0
        dd .3 - .2
    .0: db "Conurbation"
    .1: align 4
    .2: db "Bootable"
    .3: align 4
