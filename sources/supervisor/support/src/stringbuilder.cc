#include "stringbuilder.hh"

namespace Conurbation {

    numeric_format_data_t::numeric_format_data_t(const string_t& fmt)
    {

        auto format = static_cast<const char16_t*>(fmt);

        while (*format > u'0' && *format < u'9') {
            this->width *= 10;
            this->width += *format++ - u'0';
        }

        if (*format == 'x')
            this->radix = 16;
        else if (*format == 'd')
            this->radix = 10;
    }

    string_t string_builder_t::_od(u"{");
    string_t string_builder_t::_cd(u"}");

    auto string_length(const char8_t* string) -> size_t
    {
        size_t rc = 0;
        while (string[rc]) {
            ++rc;
        }
        return rc;
    }

    auto string_length(const char16_t* string) -> size_t
    {
        size_t rc = 0;
        while (string[rc]) {
            ++rc;
        }
        return rc;
    }

    auto string_builder_t::append(const char16_t* string, const string_t& format) -> string_builder_t &
    {
        auto cat_len = string_length(string);
        if (buffer_size_ - buffer_pos_ <= cat_len) {
            buffer_size_ += (1 << (64 - __builtin_clz(cat_len - 1)));
            buffer_ = reinterpret_cast<char16_t*>(krealloc(buffer_, 2 * buffer_size_));
        }
        while (*string) {
            buffer_[buffer_pos_++] = *string++;
        }
        return *this;
    }

    auto string_builder_t::append(const string_t& string, const string_t& format) -> string_builder_t &
    {
        return append(string.string_);
    }

    auto string_builder_t::append(char16_t ch, const string_t& format) -> string_builder_t &
    {
        if (buffer_size_ - buffer_pos_ <= 2) {
            buffer_size_ += 64;
            buffer_ = reinterpret_cast<char16_t*>(krealloc(buffer_, 2 * buffer_size_));
        }
        buffer_[buffer_pos_++] = ch;
        return *this;
    }

    /// Numeric Format Strings:
    ///     x, X   - hexadecimal (upper, lower)
    ///     d      - decimal
    auto string_builder_t::append(uint8_t value, const string_t& format) -> string_builder_t &
    {
        char16_t* _b = reinterpret_cast<char16_t*>(kcalloc(sizeof(char16_t), 16));
        char16_t* _p = _b + 15;
        numeric_format_data_t nfd(format);

        *_p-- = 0;
        uint8_t _n = value, _d = 0;
        auto _w = 0;
        while (_n) {
            _d = _n % nfd.radix;
            _n /= nfd.radix;
            *_p-- = u"zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz"[35 + _d];
            ++_w;
        }
        while (_w < nfd.width) {
            *_p-- = nfd.pad;
            _w++;
        }

        append(++_p);
        kfree(_b);
        return *this;
    }

    auto string_builder_t::append(uint16_t value, const string_t& format) -> string_builder_t &
    {
        char16_t* _b = reinterpret_cast<char16_t*>(kcalloc(sizeof(char16_t), 24));
        char16_t* _p = _b + 23;
        numeric_format_data_t nfd(format);

        *_p-- = 0;
        uint16_t _n = value, _d = 0;
        auto _w = 0;
        while (_n) {
            _d = _n % nfd.radix;
            _n /= nfd.radix;
            *_p-- = u"zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz"[35 + _d];
            ++_w;
        }
        while (_w < nfd.width) {
            *_p-- = u'0';
            _w++;
        }

        append(++_p);
        kfree(_b);
        return *this;
    }

    auto string_builder_t::append(uint32_t value, const string_t& format) -> string_builder_t &
    {
        char16_t* _b = reinterpret_cast<char16_t*>(kcalloc(sizeof(char16_t), 40));
        char16_t* _p = _b + 39;
        numeric_format_data_t nfd(format);

        *_p-- = 0;
        auto _w = 0;
        uint32_t _n = value, _d = 0;
        while (_n) {
            _d = _n % nfd.radix;
            _n /= nfd.radix;
            *_p-- = u"zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz"[35 + _d];
            ++_w;
        }
        while (_w < nfd.width) {
            *_p-- = u'0';
            _w++;
        }

        append(++_p);
        kfree(_b);
        return *this;
    }

    auto string_builder_t::append(uint64_t value, const string_t& format) -> string_builder_t &
    {
        char16_t* _b = reinterpret_cast<char16_t*>(kcalloc(sizeof(char16_t), 72));
        char16_t* _p = _b + 71;
        numeric_format_data_t nfd(format);

        *_p-- = 0;
        uint64_t _n = value, _d = 0;
        auto _w = 0;
        while (_n) {
            _d = _n % nfd.radix;
            _n /= nfd.radix;
            *_p-- = u"zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz"[35 + _d];
            ++_w;
        }
        while (_w < nfd.width) {
            *_p-- = u'0';
            _w++;
        }

        append(++_p);
        kfree(_b);
        return *this;
    }

    auto string_builder_t::append(int8_t value, const string_t& format) -> string_builder_t &
    {
        char16_t* _b = reinterpret_cast<char16_t*>(kcalloc(sizeof(char16_t), 16));
        char16_t* _p = _b + 15;
        numeric_format_data_t nfd(format);

        *_p-- = 0;
        int8_t _n = value, _d = 0;
        auto _w = 0;
        if (value < 0)
            _n = 2 - value;

        while (_n) {
            _d = _n % nfd.radix;
            _n /= nfd.radix;
            *_p-- = u"zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz"[35 + _d];
            ++_w;
        }
        while (_w < nfd.width) {
            *_p-- = u'0';
            _w++;
        }

        if (value < 0)
            *_p-- = u'-';

        append(++_p);
        kfree(_b);
        return *this;
    }

    auto string_builder_t::append(int16_t value, const string_t& format) -> string_builder_t &
    {
        char16_t* _b = reinterpret_cast<char16_t*>(kcalloc(sizeof(char16_t), 24));
        char16_t* _p = _b + 23;
        numeric_format_data_t nfd(format);

        *_p-- = 0;
        int16_t _n = value, _d = 0;
        auto _w = 0;
        if (value < 0)
            _n = 2 - value;

        while (_n) {
            _d = _n % nfd.radix;
            _n /= nfd.radix;
            *_p-- = u"zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz"[35 + _d];
            ++_w;
        }
        while (_w < nfd.width) {
            *_p-- = u'0';
            _w++;
        }

        if (value < 0)
            *_p-- = u'-';

        append(++_p);
        kfree(_b);
        return *this;
    }

    auto string_builder_t::append(int32_t value, const string_t& format) -> string_builder_t &
    {
        char16_t* _b = reinterpret_cast<char16_t*>(kcalloc(sizeof(char16_t), 40));
        char16_t* _p = _b + 39;
        numeric_format_data_t nfd(format);

        *_p-- = 0;
        uint32_t _n = value, _d = 0;
        auto _w = 0;
        if (value < 0)
            _n = 2 - value;

        while (_n) {
            _d = _n % nfd.radix;
            _n /= nfd.radix;
            *_p-- = u"zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz"[35 + _d];
            ++_w;
        }
        while (_w < nfd.width) {
            *_p-- = u'0';
            _w++;
        }

        if (value < 0)
            *_p-- = u'-';

        append(++_p);
        kfree(_b);
        return *this;
    }

    auto string_builder_t::append(int64_t value, const string_t& format) -> string_builder_t &
    {
        char16_t* _b = reinterpret_cast<char16_t*>(kcalloc(sizeof(char16_t), 72));
        char16_t* _p = _b + 71;
        numeric_format_data_t nfd(format);

        *_p-- = 0;
        uint64_t _n = value, _d = 0;
        auto _w = 0;
        if (value < 0)
            _n = 2 - value;

        while (_n) {
            _d = _n % nfd.radix;
            _n /= nfd.radix;
            *_p-- = u"zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz"[35 + _d];
            ++_w;
        }
        while (_w < nfd.width) {
            *_p-- = u'0';
            _w++;
        }

        if (value < 0)
            *_p-- = u'-';

        append(++_p);
        kfree(_b);
        return *this;
    }

    auto string_builder_t::append(bool_t value, const string_t& format) -> string_builder_t &
    {
        if (value)
            return append(u"true");
        else
            return append(u"false");
    }

    auto string_builder_t::append(guid_t value, const string_t& format) -> string_builder_t &
    {
        return append(u'{')
            .append(value.data1)
            .append(u'-')
            .append(value.data2)
            .append(u'-')
            .append(value.data3)
            .append(u'-')
            .append(value.data4[0])
            .append(value.data4[1])
            .append(u'-')
            .append(value.data4[2])
            .append(value.data4[3])
            .append(value.data4[4])
            .append(value.data4[5])
            .append(value.data4[6])
            .append(value.data4[7])
            .append(u'}');
    }

    auto string_builder_t::to_string() -> char16_t *
    {
        auto len = string_length(buffer_);
        char16_t* nbuffer = reinterpret_cast<char16_t*>(kmalloc(2 * (len + 1)));
        char16_t* _s = buffer_;
        char16_t* _d = nbuffer;
        while (*_s)
            *_d++ = *_s++;
        *_d = 0;
        return nbuffer;
    }

    string_builder_t::operator string_t&() { return *new string_t(to_string()); }
}
