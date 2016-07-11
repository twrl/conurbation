#pragma once

#include "numeric_types.hh"

enum class block_field_flags_t : int32_t { Object = 3, Block = 7, ByRef = 8, IsWeak = 16, ByRef_Caller = 128 };
enum class block_layout_flags_t : int32_t {
    RefcountMask = (0xffff),
    NeedsFree = (1 << 24),
    HasCopyDispose = (1 << 25),
    HasCtor = (1 << 26), /* Helpers have C++ code. */
    IsGC = (1 << 27),
    IsGlobal = (1 << 28),
    HasDescriptor = (1 << 29)
};
/* Certain field types require runtime assistance when being copied to the
   heap.  The following function is used to copy fields of types: blocks,
   pointers to byref structures, and objects (including
   __attribute__((NSObject)) pointers.  BLOCK_FIELD_IS_WEAK is orthogonal to
   the other choices which are mutually exclusive.  Only in a Block copy
   helper will one see BLOCK_FIELD_IS_BYREF.
*/
extern "C" void _Block_object_assign(void* destAddr, const void* object, const block_field_flags_t flags);

/* Similarly a compiler generated dispose helper needs to call back for each
   field of the byref data structure.  (Currently the implementation only
   packs one field into the byref structure but in principle there could be
   more).  The same flags used in the copy helper should be used for each
   call generated to this function:
*/
extern "C" void _Block_object_dispose(const void* object, const block_field_flags_t flags);

struct block_descriptor_t {
    uint64_t reserved;
    uint64_t size;
    void (*copy)(void* dst, void* src);
    void (*dispose)(void*);
};

struct block_layout_t {
    void* isa;
    int flags;
    int reserved;
    void (*invoke)(void*, ...);
    block_descriptor_t* descriptor;
    /* Imported variables. */
};

struct block_byref_t {
    void* isa;
    block_byref_t* forwarding;
    int flags; /* refcount; */
    int size;
    void (*byref_keep)(block_byref_t* dst, block_byref_t* src);
    void (*byref_destroy)(block_byref_t*);
    /* long shared[0]; */
};

struct block_byref_header_t {
    void* isa;
    block_byref_t* forwarding;
    int flags;
    int size;
};

struct block_basic_t {
    void* isa;
    int Block_flags; /* int32_t */
    int Block_size; /* XXX should be packed into Block_flags */
    void (*Block_invoke)(void*);
    void (*Block_copy)(void* dst, void* src); /* iff BLOCK_HAS_COPY_DISPOSE */
    void (*Block_dispose)(void*); /* iff BLOCK_HAS_COPY_DISPOSE */
    /* long params[0];  // where const imports, __block storage references, etc. get laid down */
};
