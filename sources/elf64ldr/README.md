## Use cases

  * **static executable** This is the simplest case, a statically linked elf64
    executable. elf64ldr loads the executable, applies relocations if necessary,
    and calls it's entry point as if it were an ordinary efi_main. It's simply
    a file format adapter.

  * **dynamic object** The next simplest case, the elf64 executable is a
    dynamic object file. elf64ldr performs the dynamic link analogous to ld.so,
    but still treats the entry point as efi_main

  * **dynamic object with libuefi** As dynamic object, but elf64ldr initializes
    libuefi and calls the entry point according to the SysV ABI.
