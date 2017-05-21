#include "string.h"

#include "ll/ucd.hh"

// These functions are lifted verbatim from PDCLib
//

#define compat extern "C" auto

compat strlen(const char* s)->size_t
{
    size_t rc = 0;
    while (s[rc]) {
        ++rc;
    }
    return rc;
}

compat strncat(char* s1, const char* s2, size_t n)->char *
{
    char* rc = s1;
    while (*s1) {
        ++s1;
    }
    while (n && (*s1++ = *s2++)) {
        --n;
    }
    if (n == 0) {
        *s1 = '\0';
    }
    return rc;
}

compat strcat(char* s1, const char* s2)->char *
{
    char* rc = s1;
    if (*s1) {
        while (*++s1)
            ;
    }
    while ((*s1++ = *s2++))
        ;
    return rc;
}

compat strchr(const char* s, size_t c)->char *
{
    do {
        if (*s == (char)c) {
            return (char*)s;
        }
    } while (*s++);
    return nullptr;
}

compat strcmp(const char* s1, const char* s2)->uint32_t
{
    while ((*s1) && (*s1 == *s2)) {
        ++s1;
        ++s2;
    }
    return (*(unsigned char*)s1 - *(unsigned char*)s2);
}

compat strcpy(char* s1, char* s2)->char *
{
    char* rc = s1;
    while ((*s1++ = *s2++))
        ;
    return rc;
}

compat srtncpy(char* s1, char* s2, size_t n)->char *
{
    char* rc = s1;
    while ((n > 0) && (*s1++ = *s2++)) {
        /* Cannot do "n--" in the conditional as size_t is unsigned and we have
           to check it again for >0 in the next loop below, so we must not risk
           underflow.
        */
        --n;
    }
    /* Checking against 1 as we missed the last --n in the loop above. */
    while (n-- > 1) {
        *s1++ = '\0';
    }
    return rc;
}

compat strncmp(const char* s1, const char* s2, size_t n)->uint32_t
{
    while (*s1 && n && (*s1 == *s2)) {
        ++s1;
        ++s2;
        --n;
    }
    if (n == 0) {
        return 0;
    }
    else {
        return (*(unsigned char*)s1 - *(unsigned char*)s2);
    }
}

compat memcmp(const void* s1, const void* s2, size_t n)->uint32_t
{
    const unsigned char* p1 = (const unsigned char*)s1;
    const unsigned char* p2 = (const unsigned char*)s2;
    while (n--) {
        if (*p1 != *p2) {
            return *p1 - *p2;
        }
        ++p1;
        ++p2;
    }
    return 0;
}
