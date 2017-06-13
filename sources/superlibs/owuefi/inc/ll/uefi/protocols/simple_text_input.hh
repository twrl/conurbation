#pragma once

#include "ll/uefi/abi.hh"

namespace ll::UEFI::Protocols {

    struct simple_text_input_p;

    typedef status_t(efiabi input_reset_f)(simple_text_input_p * _this, bool_t exendedVerification);
    typedef status_t(efiabi input_read_key_f)(simple_text_input_p * _this, input_key_t * key);

    struct simple_text_input_p {
        input_reset_f* Reset;
        input_read_key_f* ReadKeyStroke;
        event_t WaitForKey;
    };

}
