#pragma once

#include "stddef.h"
#include "stdint.h"

extern "C" void* memcpy(void* dest, const void* src, size_t count);
extern "C" void* memset(void* dest, int ch, size_t count);

// The original code for memcpy and memset comes from http://forum.osdev.org/viewtopic.php?t=18119
// and is due to a user called Jeko

/*
static inline char *memcpy(char *to, const char *from, size_t n)
{
   // We assume SSE, since this is an x86-64 kernel

   size_t i;
   for(i=0; i<n/16; i++)
   {
      __asm__ __volatile__ ("movups (%0), %%xmm0\n" "movntdq %%xmm0, (%1)\n"::"r"(from), "r"(to) : "memory");

      from += 16;
      to += 16;
   }
   
   if(n & 7)
   {
      n = n&7;

      int d0, d1, d2;
      __asm__ __volatile__(
      "rep ; movsl\n\t"
      "testb $2,%b4\n\t"
      "je 1f\n\t"
      "movsw\n"
      "1:\ttestb $1,%b4\n\t"
      "je 2f\n\t"
      "movsb\n"
      "2:"
      : "=&c" (d0), "=&D" (d1), "=&S" (d2)
      :"0" (n/4), "q" (n),"1" ((long) to),"2" ((long) from)
      : "memory");
   }
   return (to);
}

static inline char *memset(char *s, char c, size_t count)
{
   size_t d0, d1;
   __asm__ __volatile__(
   "rep\n\t"
   "stosb"
   : "=&c" (d0), "=&D" (d1)
   :"a" (c),"1" (s),"0" (count)
   :"memory");
   return s;
}

static inline char *memset32(uint32_t *s, uint32_t c, size_t count)
{
   size_t d0, d1;
   */ /*__asm__ __volatile__(
   "rep stosd"
   : "=&c" (d0), "=&D" (d1)
   :"a" (c),"1" (s),"0" (count)
   :"memory");*/ /*
                                  for (size_t i = 0; i < count; i ++) {
                                     s[i]=c;
                                  }
                                  return s;
                               }
                               */
