#pragma once

#include "conurbation/uefi/abi.hh"
#include "conurbation/uefi/efi_types.hh"
#include "conurbation/uefi/file.hh"
#include "jones/jones_loadable.hh"

namespace Jones {

    struct jones_loader_p;

    typedef Conurbation::UEFI::status_t(efiabi can_load_f)(jones_loader_p* loader, Conurbation::UEFI::efi_file_p* file);
    typedef Conurbation::UEFI::status_t(efiabi prepare_load_f)(jones_loader_p* loader, Conurbation::UEFI::handle_t fileHandle, Conurbation::UEFI::efi_file_p* file, jones_loadable_p** loadable);

    struct jones_loader_p {
        can_load_f* CanLoad;
        prepare_load_f* PrepareLoad;
    };

}

template <> guid_t Conurbation::UEFI::protocol_guid_v<Jones::jones_loader_p> = "89cfa780-1d79-434b-9efb-52d6a87f701c"_guid;
