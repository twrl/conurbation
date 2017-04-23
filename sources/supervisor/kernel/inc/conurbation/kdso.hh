#pragma once

#include "conurbation/char_types.hh"
#include "conurbation/elf64.hh"

namespace Conurbation {

    struct kdso_t {
        cstring8_t soname;

        kdso_t** needed;

        elf64_sym_t* dynsym;

        cstring8_t dynstr;


    };

}
