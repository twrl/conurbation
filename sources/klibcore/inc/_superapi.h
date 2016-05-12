#pragma once

#ifdef __cplusplus
#define _libsuper_begin_capi                                                                                                  \
    namespace std {                                                                                                           \
        extern "C" {
#define _libsuper_end_capi                                                                                                    \
    }                                                                                                                         \
    }
#else
#define _libsuper_begin_capi
#define _libsuper_end_capi
#endif

#define _cat2(A, B) A##B
#define _cat(A, B) _cat2(A, B)
