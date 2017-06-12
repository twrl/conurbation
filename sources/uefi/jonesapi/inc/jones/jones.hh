#pragma once

#include "conurbation/uefi/abi.hh"
#include "conurbation/uefi/efi_types.hh"
#include "conurbation/uefi/protocol/device_path.hh"
#include "jones/jones_loadable.hh"

namespace Jones {

    struct jones_p;

    typedef Conurbation::UEFI::status_t(efiabi get_loader_f)(Conurbation::UEFI::efi_device_path_p* path, jones_loadable_p** loadable);

    struct jones_p {
        get_loader_f* GetLoader;
    };

}

//extern template <> guid_t Conurbation::UEFI::protocol_guid_v<Jones::jones_p>;
