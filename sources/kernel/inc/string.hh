#pragma once

#include "char_types.hh"

#include "conurbation/mem/liballoc.h"
#include "string.h"

namespace Conurbation {

    enum class encoding_t { utf8, utf16, utf32 };

    class string_t {
        friend class string_builder_t;

    private:
        const char16_t* string_;
        static const char16_t empty_ch_;
        static string_t* empty_;

        string_t(nullptr_t n)
            : string_(&empty_ch_)
        {
        }

    public:
        string_t(string_t& str)
            : string_(reinterpret_cast<const char16_t*>(kmalloc(str.size())))
        {
            memcpy(const_cast<void*>(reinterpret_cast<const void*>(string_)),
                const_cast<void*>(reinterpret_cast<const void*>(str.string_)), str.size());
        }

        constexpr string_t(const char16_t* cstring)
            : string_(cstring)
        {
        }

        string_t(string_t&& str)
            : string_(str.string_)
        {
            str.string_ = nullptr;
        }

        static auto empty() -> string_t&;

        ~string_t() { kfree(const_cast<void*>(reinterpret_cast<const void*>(string_))); }

        // Length in unicode code points (i.e. number of unicode characters, not including terminal null)
        auto length() const -> size_t;

        // Size in bytes (including the terminal null)
        auto size() const -> size_t;

        auto starts_with(string_t& string) const -> bool_t;

        auto ends_with(string_t& string) const -> bool_t;

        // auto concat(string_t& str) -> string_t&;

        // auto contains(string_t& string) const -> bool_t;

        // auto contains(const char32_t ch) const -> bool_t;

        // auto index_of(const char32_t ch) const -> size_t;

        auto index_of(string_t& str) const -> size_t;

        // Given a starting position, find the first occurance of str after that
        auto index_after(string_t& str, size_t from) const -> size_t;

        // auto last_index_of(const char32_t ch) -> size_t;

        // auto last_index_of(string_t& str) -> size_t;

        auto is_empty() const -> bool_t;

        // auto normalize() -> string_t&;

        auto substring(size_t start) const -> string_t&;

        auto substring(size_t start, size_t end) const -> string_t&;

        // auto to_upper() -> string_t&;

        // auto to_lower() -> string_t&;

        // auto trim_left() -> string_t&;

        // auto trim_right() -> string_t&;

        // auto trim() -> string_t&;

        // inline auto operator+(string_t& str) -> string_t & { return this->concat(str); }

        // inline auto operator+=(string_t& str) -> string_t & { return this->concat(str); }

        [[deprecated]] operator const char16_t*() const { return string_; }

        auto operator=(const string_t& str) -> string_t &
        {
            kfree(const_cast<void*>(reinterpret_cast<const void*>(string_)));
            string_ = reinterpret_cast<const char16_t*>(kmalloc(str.size()));
            memcpy(const_cast<void*>(reinterpret_cast<const void*>(string_)),
                const_cast<void*>(reinterpret_cast<const void*>(str.string_)), str.size());
            return *this;
        }
    };
}
