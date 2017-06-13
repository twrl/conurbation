#pragma once

#include "ll/uefi/abi.hh"

namespace ll::UEFI::Tables {

    struct configuration_t {
        guid_t VendorGuid;
        void* VendorTable;
    };

}
