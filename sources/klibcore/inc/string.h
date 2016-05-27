#ifndef _STRING_H_
#define _STRING_H_

#ifdef __cplusplus
#define restrict
extern "C" {
#endif

void* memcpy(void* restrict dest, const void* src, __SIZE_TYPE__ count);
void* memmove(void* restrict dest, void* src, __SIZE_TYPE__ count);
void* memset(void* restrict dest, unsigned char value, __SIZE_TYPE__ count);
int memcmp(const void* s1, const void* s2, __SIZE_TYPE__ n);

__SIZE_TYPE__ strlen(const char* s);
char* strncat(char* restrict s1, const char* restrict s2, __SIZE_TYPE__ n);
char* strcat(char* restrict s1, const char* restrict s2);
char* strchr(const char* s, int c);
int strcmp(const char* s1, const char* s2);
char* strcpy(char* restrict s1, const char* restrict s2);
char* strncpy(char* restrict s1, const char* restrict s2, __SIZE_TYPE__ n);
int strncmp(const char* s1, const char* s2, __SIZE_TYPE__ n);

#ifdef __cplusplus
}
#endif

#endif
