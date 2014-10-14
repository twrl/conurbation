#pragma once

#ifdef __SIZE_TYPE__
typedef __SIZE_TYPE__       size_t;
#else 
typedef unsigned long       size_t;
#endif

#ifdef __PTRDIFF_TYPE__
typedef __PTRDIFF_TYPE__    ptrdiff_t;
#else
typedef signed long         ptrdiff_t;
#endif

