#pragma once

#ifndef __cplusplus
#error "Cannot include pure C++ header in C code"
#endif

namespace Conurbation::ObModel
{

    class component_t {
    private:
        system_t* system_;
        entity_t* entity_;

        component_t* next_in_system_;
        component_t* next_in_entity_;

    public:
    }
}
