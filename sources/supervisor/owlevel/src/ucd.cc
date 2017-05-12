#include "char_types.hh"
#include "ll/unicode_props.hh"
#include "ll/ucd.hh"

namespace ll::Unicode {
    
    ucd_name_t const* ucd_names = {
#include "./ucd/name.g.inl"
    };
    
    ucd_category_t const* ucd_categories = {
#include "./ucd/category.g.inl"
    };
    
    ucd_block_t const* ucd_blocks = {
#include "./ucd/block.g.inl"  
    };
    
}