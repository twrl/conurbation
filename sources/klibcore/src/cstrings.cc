#include "string.h"

// These functions are lifted verbatim from PDCLib
//

using std::size_t;

#ifdef __cplusplus
#define restrict
extern "C" {
#endif

size_t strlen(const char* s)
{
    size_t rc = 0;
    while (s[rc]) {
        ++rc;
    }
    return rc;
}

char* strncat(char* restrict s1, const char* restrict s2, size_t n)
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

char* strcat(char* restrict s1, const char* restrict s2)
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

char* strchr(const char* s, int c)
{
    do {
        if (*s == (char)c) {
            return (char*)s;
        }
    } while (*s++);
    return nullptr;
}

int strcmp(const char* s1, const char* s2)
{
    while ((*s1) && (*s1 == *s2)) {
        ++s1;
        ++s2;
    }
    return (*(unsigned char*)s1 - *(unsigned char*)s2);
}

char* strcpy(char* restrict s1, const char* restrict s2)
{
    char* rc = s1;
    while ((*s1++ = *s2++))
        ;
    return rc;
}

char* strncpy(char* restrict s1, const char* restrict s2, size_t n)
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

int strncmp(const char* s1, const char* s2, size_t n)
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

int memcmp(const void* s1, const void* s2, size_t n)
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

#ifdef __cplusplus
}
#undef restrict
#endif
