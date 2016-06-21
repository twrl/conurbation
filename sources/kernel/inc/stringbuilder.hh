#pragma once

#include "char_types.hh"
#include "numeric_types.hh"
#include "guid.h"
#include "conurbation/mem/liballoc.h"
#include "string.hh"

namespace Conurbation {

    struct numeric_format_data_t {
        numeric_format_data_t(const string_t&);
        char16_t group_separator = u',';
        char16_t decimal_point = u'.';
        char16_t pad = u'0';
        uint8_t radix = 10;
        uint8_t width = 0;
        uint8_t group_width = 3;
    };

    class string_builder_t {
    private:
        char16_t* buffer_;
        ptrdiff_t buffer_pos_;
        size_t buffer_size_;

        static string_t _od;
        static string_t _cd;

    public:
        string_builder_t(size_t icapacity)
            : buffer_(reinterpret_cast<char16_t*>(kcalloc(icapacity, sizeof(char16_t))))
            , buffer_pos_(0)
            , buffer_size_(icapacity)
        {
        }
        string_builder_t()
            : string_builder_t(128)
        {
        }

        ~string_builder_t() { kfree(reinterpret_cast<void*>(buffer_)); }

        auto append(const char16_t* string) -> string_builder_t&;
        auto append(const string_t& string) -> string_builder_t&;
        auto append(char16_t ch) -> string_builder_t&;

        auto append(uint8_t value, const string_t& format = u"2x") -> string_builder_t&;
        auto append(uint16_t value, const string_t& format = u"4x") -> string_builder_t&;
        auto append(uint32_t value, const string_t& format = u"8x") -> string_builder_t&;
        auto append(uint64_t value, const string_t& format = u"16x") -> string_builder_t&;

        auto append(int8_t value, const string_t& format = u"d") -> string_builder_t&;
        auto append(int16_t value, const string_t& format = u"d") -> string_builder_t&;
        auto append(int32_t value, const string_t& format = u"d") -> string_builder_t&;
        auto append(int64_t value, const string_t& format = u"d") -> string_builder_t&;

        auto append(bool_t value, const string_t& format = u"") -> string_builder_t&;

        auto append(guid_t value, const string_t& format = u"") -> string_builder_t&;

        // template <typename T> auto append(T value) -> string_builder_t & { return append(value.to_string()); }

        auto to_string() -> char16_t*;

        operator string_t&();

        template <typename THead, typename... TRest>
        auto append_format(string_t& format, THead hval, TRest... tvals) -> string_builder_t &
        {
            auto _i = format.index_of(_od);
            auto _j = format.index_after(_cd, _i + 1);
            return this->append(format.substring(0, _i - 1))
                .append(hval, format.substring(_i + 1, _j - 1))
                .append_format(format.substring(_j + 1), tvals...);
        }

        template <typename THead> auto append_format(string_t& format, THead hval) -> string_builder_t &
        {
            auto _i = format.index_of(_od);
            auto _j = format.index_after(_cd, _i + 1);
            return this->append(format.substring(0, _i - 1))
                .append(hval, format.substring(_i + 1, _j - 1))
                .append(format.substring(_j + 1));
        }

        auto append_format(string_t& format) -> string_builder_t & { return append(format); }
    };

    [[deprecated]] auto string_length(const char8_t* string) -> size_t;
    [[deprecated]] auto string_length(const char16_t* string) -> size_t;

    template <typename... TArgs> auto format(string_t&& format_string, TArgs... args) -> string_t &
    {
        string_builder_t sb;
        return sb.append_format(format_string, args...);
    }
}
