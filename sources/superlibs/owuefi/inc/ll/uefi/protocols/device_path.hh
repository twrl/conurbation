#pragma once

#include "ll/uefi/abi.hh"

namespace ll::UEFI::Protocols {

    enum class device_path_type_t: uint8_t {
        hardware = 1,
        acpi = 2,
        messaging = 3,
        media = 4,
        bbs = 5,

        END = 0x7f
    };

    struct device_path_p {
        device_path_type_t Type;
        uint8_t Subtype;
        uint16_t Length;
    };

    struct pci_device_path_p: device_path_p {
        uint8_t Function;
        uint8_t Device;
    };

    struct pccard_device_path_p: device_path_p {
        uint8_t Function;
    };

    struct memmapped_device_path_p: device_path_p {
        memory_type_t MemoryType;
        uint64_t StartAddress;
        uint64_t EndAddress;
    };


}
