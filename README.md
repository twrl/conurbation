     _____                        _           _   _             
    /  __ \                      | |         | | (_)            
    | /  \/ ___  _ __  _   _ _ __| |__   __ _| |_ _  ___  _ __  
    | |    / _ \| '_ \| | | | '__| '_ \ / _` | __| |/ _ \| '_ \
    | \__/\ (_) | | | | |_| | |  | |_) | (_| | |_| | (_) | | | |
     \____/\___/|_| |_|\__,_|_|  |_.__/ \__,_|\__|_|\___/|_| |_|




[![Build Status](https://travis-ci.org/twrl/conurbation.svg?branch=taketwo)](https://travis-ci.org/twrl/conurbation)

This is the rewrite of my hobby operating system, which is a bit of a playground. Major developments are coming irregularly at the moment while I'm still merging in various past experiments and side projects.

The system is being written to be legacy-free. It assumes x64, SSE2, ACPI >5.0, and UEFI 2.x.

## Build Instructions

You will need:

* clang 3.8
* nasm
* binutils 2.26
* ninja
* python 2.7
* gnu-efi 3.0.3
* GN

On Ubuntu trusty and derivatives you can obtain these by just following the commands in the `.travis.yml` file. GN must be downloaded from Google Storage using the command

```bash
python ./build/depot_tools/download_from_google_storage.py -b chromium-gn -s ./build/tools/gn.sha1
```

To build, first have GN initialize a build directory by doing, for example
```bash
build/tools/gn gen build/out
```
then invoke ninja
```bash
ninja -C build/out
```

An up to date build of the OVMF firmware is included in the `build/vm/OVMF` directory for testing on a virtual machine. OVMF r15214, which is available as a binary download from the EDK2 project, is out of date and has limited ACPI support.

I test with a command like
```bash
qemu-system-x86_64 -pflash build/vm/OVMF/OVMF.fd -drive file=fat:build/out,if=ide
```

At the moment QEMU is just synthesising a FAT hard disk from the build output directory. At some point I'll set up proper image generation.
