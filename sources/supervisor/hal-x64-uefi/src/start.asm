[BITS 64]

[SECTION .text]

[EXTERN halmain]

_start:
        call halmain
        cli
        hlt
        