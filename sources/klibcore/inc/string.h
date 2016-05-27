#pragma once

#include "numeric_types.hh"
#define compat extern "C" auto

compat memcpy(void* dest, void* src, size_t count)->void*;
compat memmove(void* dest, void* src, size_t count)->void*;
compat memset(void* dest, void* value, size_t count)->void*;

compat memcmp(const void* s1, const void* s2, size_t n)->uint32_t;

compat strlen(const char* s)->size_t;
compat strncat(char* s1, const char* s2, size_t n)->char*;
compat strcat(char* s1, const char* s2)->char*;
compat strchr(const char* s, size_t c)->char*;
compat strcmp(const char* s1, const char* s2)->uint32_t;
compat strcpy(char* s1, char* s2)->char*;
compat srtncpy(char* s1, char* s2, size_t n)->char*;
compat strncmp(const char* s1, const char* s2, size_t n)->uint32_t;

#undef compat
