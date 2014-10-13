OUTPUT_FORMAT("elf64-x86-64")
ENTRY(_start)

SECTIONS
{
    .text : ALIGN(0x1000) {
        *(.text*)
    }
    .rodata : ALIGN(0x1000) {
        *(.rodata)
    }
    .eh_frame_hdr : ALIGN(0x1000) {
        *(.eh_frame_hdr)
    }
    .eh_frame : ALIGN(0x1000) {
        *(.eh_frame)
    }
    .init_array : ALIGN(0x1000) {
    init_array_start = .;
        *(.init_array)
    init_array_end = .;
    }
    .data : ALIGN(0x1000) {
        *(.data)
    }
    .bss : ALIGN(0x1000) {
        *(.bss)
    }
}

