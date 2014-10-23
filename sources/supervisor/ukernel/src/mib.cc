#include "ConSup/mib.h"
#include "new.h"
#include "string.h"

ConSup::mib_c* ConSup::kernel_root_mib;

struct ConSup::mib_c::child_tree_t {
    uintptr_t index;
    mib_c* child;
    child_tree_t* left;
    child_tree_t* right;
};

auto ConSup::mib_c::getValue() -> chunk_t* {
    chunk_t* newChunkRef = new chunk_t();
    void* clone = malloc(this->_dataSize);
    memcpy(clone, this->_data, this->_dataSize);
    newChunkRef->base = clone;
    newChunkRef->size = this->_dataSize;
    return newChunkRef;
}

auto ConSup::mib_c::setValue(chunk_t* value) -> void {
    void* oldData = this->_data;
    // oldSize?
    this->_data = malloc(value->size);
    memcpy(this->_data, value->base, value->size);
    free(oldData);
    this->_dataSize = value->size;
}

ConSup::mib_c* ConSup::mib_c::getChildNode(ConSup::mib_c::child_tree_t** rt, uintptr_t index) {
    if (!*rt) {
        return nullptr;
    } else {
        if ((*rt)->index == index) {
            return (*rt)->child;
        } else if ((*rt)->index > index) {
            return getChildNode(&(*rt)->left, index);
        } else {
            return getChildNode(&(*rt)->right, index);
        }
    }
}

auto ConSup::mib_c::getChild(uintptr_t index) -> ConSup::mib_c* {
    return getChildNode(&this->_childRoot, index);
}

void ConSup::mib_c::addChildNode(ConSup::mib_c::child_tree_t** rt, uintptr_t index,
                                 ConSup::mib_c* child) {
    if (!*rt) {
        *rt = new ConSup::mib_c::child_tree_t();
        (*rt)->index = index;
        (*rt)->child = child;
        (*rt)->left = nullptr;
        (*rt)->right = nullptr;
    } else {
        if ((*rt)->index > index) {
            addChildNode(&(*rt)->left, index, child);
        } else {
            addChildNode(&(*rt)->right, index, child);
        }
    }
}

auto ConSup::mib_c::addChild(uintptr_t index, ConSup::mib_c* child) -> void {
    addChildNode(&this->_childRoot, index, child);
}

auto ConSup::mib_c::removeChild(uintptr_t index) -> void {
    // TODO: Implement me!
}

auto ConSup::mib_c::get(ConSup::mibref_t ref) -> chunk_t* {
    uintptr_t current = *ref++;
    if (current) {
        return this->getChild(current)->get(ref);
    } else {
        return this->getValue();
    }
}

auto ConSup::mib_c::set(ConSup::mibref_t ref, chunk_t* value) -> void {
    uintptr_t current = *ref++;
    if (current) {
        // FIXME: What if child doesn't exist?
        ConSup::mib_c* child = this->getChild(current);
        if (!child) {
            child = new ConSup::mib_c();
            this->addChild(current, child);
        }
        child->set(ref, value);
    } else {
        this->setValue(value);
    }
}
