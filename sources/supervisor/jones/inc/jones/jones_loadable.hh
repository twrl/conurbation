#pragma once

#include "conurbation/uefi/abi.hh"
#include "conurbation/uefi/efi_types.hh"

namespace Jones {

    struct jones_loadable_p;

    struct jones_loadable_p {

    };

}

template <> guid_t Conurbation::UEFI::protocol_guid_v<Jones::jones_loadable_p> = "851964ce-c8c3-4ae0-aac9-b2895fc68a2f"_guid;
