#include "conurbation/heap/bestfit.hh"
#include "conurbation/string.h"

namespace {

    struct free_node_t {
        size_t nodeSize;
        free_node_t* left;
        free_node_t* right;
    };

    auto insert_free_node(free_node_t* subtree, void* ptr, size_t size) -> free_node_t* {
        if (subtree == nullptr) {
            free_node_t* newNode = reinterpret_cast<free_node_t*>(ptr);
            newNode->nodeSize = size;
            newNode->left = nullptr;
            newNode->right = nullptr;
            return newNode;
        } else if (size < subtree->nodeSize) {
            subtree->left = insert_free_node(subtree->left, ptr, size);
        } else {
            subtree->right = insert_free_node(subtree->right, ptr, size);
        }
        return subtree;
    }
}

Conurbation::Heap::bestfit_t::bestfit_t() noexcept {}
Conurbation::Heap::bestfit_t::bestfit_t(void* firstblock, size_t firstblockSize) noexcept {
    this->deallocate(firstblock, firstblockSize, 0);
}

auto Conurbation::Heap::bestfit_t::allocate (size_t size, size_t align) -> result_t<void*> {
    // Find the smallest free node b such that b->nodeSize >= size && b->left->nodeSize < size
    return status_t::notImplemented;
}

auto Conurbation::Heap::bestfit_t::deallocate (void* ptr, size_t old_size, size_t align) -> status_t {
    if (old_size >= sizeof(free_node_t)) {
        this->root_ = insert_free_node(this->root_, ptr, old_size);
        return status_t::success;
    } else return status_t::tooSmall;
}

auto Conurbation::Heap::bestfit_t::reallocate (void* ptr, size_t old_size, size_t new_size, size_t align) -> result_t<void*> {
    auto v = this->allocate(new_size, align);
    if (v) {
        memcpy(v.some(), ptr, old_size);
        this->deallocate(ptr, old_size, align);
    }
    return v;
}
