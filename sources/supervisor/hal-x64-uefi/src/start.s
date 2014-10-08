[BITS 64]

[SECTION .text]

[EXTERN halmain]
[GLOBAL _start:function]
_start:
        call halmain
        cli
        hlt
        