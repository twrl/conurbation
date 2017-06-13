#pragma once

#include "ll/uefi/abi.hh"

namespace Jones {

    struct jones_loadable_p;

    typedef ll::UEFI::status_t (efiabi load_image_f)(jones_loadable_p* loadable);
    typedef ll::UEFI::status_t (efiabi run_image_f)(jones_loadable_p* loadable);

    struct jones_loadable_p {
        load_image_f* Load;
        run_image_f* Run;

    };

}

//extern template <> guid_t Conurbation::UEFI::protocol_guid_v<Jones::jones_loadable_p>;
