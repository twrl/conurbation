
// FIXME: This is a bit (a lot) of a rip-off of the sprintf from ToaruOS

#include "numeric_types.hh"
#include "conurbation/numeric_traits.hh"
#include "variadic.hh"

namespace {

    /*
     * Integer to string
     */
    static void print_dec(unsigned int value, unsigned int width, char16_t* buf, int* ptr)
    {
        unsigned int n_width = 1;
        unsigned int i = 9;
        while (value > i && i < Conurbation::numeric_max_v<uint32_t>) {
            n_width += 1;
            i *= 10;
            i += 9;
        }

        int printed = 0;
        while (n_width + printed < width) {
            buf[*ptr] = u' ';
            *ptr += 1;
            printed += 1;
        }

        i = n_width;
        while (i > 0) {
            unsigned int n = value / 10;
            int r = value % 10;
            buf[*ptr + i - 1] = r + u'0';
            i--;
            value = n;
        }
        *ptr += n_width;
    }

    /*
     * Hexadecimal to string
     */
    static void print_hex(uint64_t value, unsigned int width, char16_t* buf, int* ptr)
    {
        int i = width;

        if (i == 0)
            i = 8;

        unsigned int n_width = 1;
        uint64_t j = 0x0F;
        while (value > j && j < Conurbation::numeric_max_v<uint64_t>) {
            n_width += 1;
            j *= 0x10;
            j += 0x0F;
        }

        while (i > (int)n_width) {
            buf[*ptr] = '0';
            *ptr += 1;
            i--;
        }

        i = (int)n_width;
        while (i-- > 0) {
            buf[*ptr] = u"0123456789abcdef"[(value >> (i * 4)) & 0xF];
            *ptr += +1;
        }
    }
}
/*
 * vasprintf()
 */
size_t vasprintf(char16_t* buf, const char16_t* fmt, va_list args)
{
    int i = 0;
    char16_t* s;
    char16_t* b = buf;
    for (const char16_t* f = fmt; *f; f++) {
        if (*f != u'%') {
            *b++ = *f;
            continue;
        }
        ++f;
        unsigned int arg_width = 0;
        while (*f >= u'0' && *f <= u'9') {
            arg_width *= 10;
            arg_width += *f - u'0';
            ++f;
        }
        /* fmt[i] == '%' */
        switch (*f) {
            case u's': /* String pointer -> String */
                s = (char16_t*)va_arg(args, char16_t*);
                if (s == nullptr) {
                    s = const_cast<char16_t*>(u"(null)");
                }
                while (*s) {
                    *b++ = *s++;
                }
                break;
            case u'c': /* Single character */
                *b++ = (char16_t)va_arg(args, int);
                break;
            case u'x': /* Hexadecimal number */
                i = b - buf;
                print_hex((unsigned long)va_arg(args, unsigned long), arg_width, buf, &i);
                b = buf + i;
                break;
            case u'd': /* Decimal number */
                i = b - buf;
                print_dec((unsigned long)va_arg(args, unsigned long), arg_width, buf, &i);
                b = buf + i;
                break;
            case u'%': /* Escape */
                *b++ = u'%';
                break;
            default: /* Nothing at all, just dump it */
                *b++ = *f;
                break;
        }
    }
    /* Ensure the buffer ends in a null */
    *b = u'\0';
    return b - buf;
}

int sprintf(char16_t* buf, const char16_t* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    int out = vasprintf(buf, fmt, args);
    va_end(args);
    return out;
}
