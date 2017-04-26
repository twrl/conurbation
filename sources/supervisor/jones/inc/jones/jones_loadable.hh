#pragma once

#include "conurbation/uefi/abi.hh"
#include "conurbation/uefi/efi_types.hh"

namespace Jones {

    struct jones_loadable_p;

    typedef Conurbation::UEFI::status_t (efiabi load_image_f)(jones_loadable_p* loadable);
    typedef Conurbation::UEFI::status_t (efiabi run_image_f)(jones_loadable_p* loadable);

    struct jones_loadable_p {
        load_image_f* Load;
        run_image_f* Run;

    };

}

template <> guid_t Conurbation::UEFI::protocol_guid_v<Jones::jones_loadable_p> = "851964ce-c8c3-4ae0-aac9-b2895fc68a2f"_guid;
