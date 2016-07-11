#include "blocks.hh"
#include "string.h"

void* _NSConcreteStackBlock[32] = { 0 };
void* _NSConcreteMallocBlock[32] = { 0 };
void* _NSConcreteAutoBlock[32] = { 0 };
void* _NSConcreteFinalizingBlock[32] = { 0 };
void* _NSConcreteGlobalBlock[32] = { 0 };
void* _NSConcreteWeakBlockVariable[32] = { 0 };

#if 0

#define test_flags(Var, Flags) ((Var & Flags) == Flags)

static int latching_incr_int(int* where)
{
    while (1) {
        int old_value = *(volatile int*)where;
        if ((old_value & (int)block_layout_flags_t::RefcountMask) == (int)block_layout_flags_t::RefcountMask) {
            return (int)block_layout_flags_t::RefcountMask;
        }
        if (__sync_bool_compare_and_swap((volatile int*)where, old_value, old_value + 1)) {
            return old_value + 1;
        }
    }
}

static void* _Block_copy_internal(const void* arg, const int flags)
{
    block_layout_t* aBlock;
    bool wantsOne = ((1 << 16) & flags) == (1 << 16);

    if (!arg)
        return nullptr;

    aBlock = reinterpret_cast<block_layout_t*>(arg);
    if (aBlock->flags & block_layout_flags_t::NeedsFree) {
        latching_incr_int(&aBlock->flags);
        return aBlock;
    }
};

extern "C" void _Block_object_assign(void* destAddr, const void* object, const block_field_flags_t flags)
{
    if (test_flags(flags, block_field_flags_t::ByRef_Caller)) {
        if (test_flags(flags, block_field_flags_t::IsWeak)) {
            _Block_assign_weak(object, destAddr);
        }
        else {
            _Block_assign(const_cast<void*>(object), destAddr);
        }
    }
    else if (test_flags(flags, block_field_flags_t::ByRef)) {
        _Block_byref_assign_copy(destAddr, object, flags);
    } else if (test_flags(flags, block_field_flags_t::Block) {
        _Block_assign(_Block_copy_internal(object, flags), destAddr);
    } else if (test_flags(flags, block_field_flags_t::Object)) {
        _Block_retain_object(object);
        _Block_assign(const_cast<void*>(object), destAddr);
    }
};

extern "C" void _Block_object_dispose(const void* object, const block_field_flags_t flags){

};

#endif
