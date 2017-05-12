#pragma once 

#include "char_types.hh"
#include "numeric_types.hh"
#include "ll/unicode_props.hh"

namespace ll::Unicode {
    
    struct ucd_name_t {
        char32_t code_point;
        bool_t var;
        const char8_t* character_name;
    };
    
    struct ucd_category_t {
        char32_t code_point;
        category category;
    };
    
    struct ucd_block_t {
        char32_t code_point;
        block block;
    };
    
    constexpr ucd_name_t const ucd_names[] = {
#include "./ucd/name.g.inl"
    };
    constexpr ucd_category_t const ucd_categories[] = {
#include "./ucd/category.g.inl"        
    };
    constexpr ucd_block_t const ucd_blocks[] = {
#include "./ucd/block.g.inl"        
    };
    
    
}