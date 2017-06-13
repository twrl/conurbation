#pragma once

#include "ll/uefi/abi.hh"
#include "ll/uefi/protocols/device_path.hh"
#include "jones/jones_loadable.hh"

namespace Jones {

    struct jones_p;

    typedef ll::UEFI::status_t(efiabi get_loader_f)(ll::UEFI::Protocols::device_path_p* path, jones_loadable_p** loadable);

    struct jones_p {
        get_loader_f* GetLoader;
    };

}

//extern template <> guid_t Conurbation::UEFI::protocol_guid_v<Jones::jones_p>;
