#pragma once

#include "types.h"

namespace ConSup {

    enum class address_map_type_t { empty, physmem, physmemMMIO } struct address_map_info_t {
        chunk_t virtualRange;
        chunk_t target;
        address_map_type_t mappingType;
        bool_t W, X, G, S;
    };

    class addressp_c {
        private:
        struct address_range_node_t;

        address_range_node_t* _root;

        public:
    }
}
