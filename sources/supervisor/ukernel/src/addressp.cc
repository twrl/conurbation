#include "ConSup/addressp.h"

struct address_range_node_t {
    address_map_info_t mapInfo;
    address_range_node_t* left;
    address_range_node_t* right;
};
