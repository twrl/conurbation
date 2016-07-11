#include "string.hh"

namespace Conurbation {

    const char16_t string_t::empty_ch_ = 0;
    string_t* string_t::empty_;

    auto string_t::empty() -> string_t &
    {
        if (!empty_)
            empty_ = new string_t(nullptr);
        return *empty_;
    }

    auto string_t::length() const -> size_t
    {
        const char16_t* _c = string_;
        size_t _i = 0;

        while (*_c) {
            ++_c;
            ++_i;
        }

        return _i;
    }

    auto string_t::size() const -> size_t { return sizeof(char16_t) * (length() + 1); }

    auto string_t::starts_with(string_t& str) const -> bool_t
    {
        if (length() < str.length())
            return false;

        const char16_t* _a = string_;
        const char16_t* _b = str.string_;

        while (*_b)
            if (*_b++ != *_a++)
                return false;

        return true;
    }

    auto string_t::ends_with(string_t& str) const -> bool_t
    {
        if (length() < str.length())
            return false;

        const char16_t* _a = &string_[length() - 1];
        const char16_t* _b = &str.string_[str.length() - 1];

        while (*_b)
            if (*_b-- != *_a--)
                return false;

        return true;
    }

    // TODO: Concat
    // TODO: Contains (char)
    // TODO: Contains (str)
    // TODO: IndexOf (char)

    auto string_t::index_of(string_t& str) const -> size_t
    {
        if (length() < str.length())
            return -1;

        const char16_t* _a = string_;
        const char16_t* _b = str.string_;
        size_t _i = 0;

        while (_a[_i] != _b[0])
            ++_i;

        if (length() - _i < str.length())
            return -1;

        _a = &_a[_i];
        while (*_b)
            if (*_b++ != *_a++)
                return -1;

        // FIXME: This algorithm is so so wrong, because it only tries to match the first time it encouters the first character
        // in str

        return _i;
    }

    auto string_t::index_after(string_t& str, size_t from) const -> size_t
    {
        if (length() - from < str.length())
            return -1;

        size_t _i = from;
        const char16_t* _b = str.string_;
        const char16_t* _a = string_;

        while (_a[_i] != _b[0])
            ++_i;

        if (length() - _i < str.length())
            return -1;

        _a = &_a[_i];
        while (*_b)
            if (*_b++ != *_a++)
                return -1;
        return _i;
    }

    // TODO: LastIndexOf (char)
    // TODO: LastIndexOf (str)

    auto string_t::is_empty() const -> bool_t { return string_ || *string_ == 0; }

    // TODO: Normalize

    auto string_t::substring(size_t start) const -> string_t & { return substring(start, length() - 1); }

    auto string_t::substring(size_t start, size_t end) const -> string_t &
    {
        if (end >= length() || start > end)
            return empty();

        size_t _nlen = end - start + 1;
        char16_t* _nbuf = reinterpret_cast<char16_t*>(kcalloc(_nlen + 1, sizeof(char16_t)));
        char16_t* _a = _nbuf;
        size_t _i = start;

        while (_i <= end) {
            *_a++ = string_[_i++];
        }
        *_a = 0;
        return *new string_t(_nbuf);
    }
}
