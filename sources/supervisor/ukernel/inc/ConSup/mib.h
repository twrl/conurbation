#pragma once

#include "types.h"

namespace ConSup {

    typedef uintptr_t* mibref_t;

    class mib_c {

        private:
        struct child_tree_t;

        void addChildNode(ConSup::mib_c::child_tree_t** rt, uintptr_t index, ConSup::mib_c* child);
        ConSup::mib_c* getChildNode(ConSup::mib_c::child_tree_t** rt, uintptr_t index);

        void* _data = nullptr;
        size_t _dataSize = 0;
        child_tree_t* _childRoot = nullptr;

        public:
        auto getValue() -> chunk_t*;
        auto setValue(chunk_t* value) -> void;

        auto getChild(uintptr_t index) -> mib_c*;
        auto addChild(uintptr_t index, mib_c* child) -> void;
        auto removeChild(uintptr_t index) -> void;

        auto get(mibref_t ref) -> chunk_t*;
        auto set(mibref_t ref, chunk_t* value) -> void;
    };

    // TODO: Name to mibref lookup

    extern mib_c* kernel_root_mib;
}
