#pragma once

#include "ll/uefi/abi.hh"
#include "ll/uefi/protocols/file.hh"
#include "jones/jones_loadable.hh"

namespace Jones {

    struct jones_loader_p;

    typedef ll::UEFI::status_t(efiabi can_load_f)(jones_loader_p* loader, ll::UEFI::Protocols::file_p* file);
    typedef ll::UEFI::status_t(efiabi prepare_load_f)(jones_loader_p* loader, ll::UEFI::handle_t fileHandle, ll::UEFI::Protocols::file_p* file, jones_loadable_p** loadable);

    struct jones_loader_p {
        can_load_f* CanLoad;
        prepare_load_f* PrepareLoad;
    };

}


//extern template <> guid_t Conurbation::UEFI::protocol_guid_v<Jones::jones_loader_p>;
