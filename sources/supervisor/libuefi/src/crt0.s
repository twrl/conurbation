[BITS 64]

[GLOBAL _start:function]
[EXTERN efi_main]

_start:
        call efi_main