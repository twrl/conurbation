#pragma once

#include "numeric_types.hh"
#include "ll/result.hh"

namespace ll {

    class memory_t final {

    private:
        uintptr_t base_;
        size_t size_;

    public:

        constexpr memory_t(uintptr_t base, size_t size) : base_(base), size_(size) {}
        memory_t (void* ptr, size_t size) : base_(reinterpret_cast<uintptr_t>(ptr)), size_(size) {}

        inline auto copy_to(memory_t& destination) -> status_t {
            if (this->size_ != destination.size_) return status_t::size_mismatch;
            if (this->base_ == destination.base_) return status_t::success;

            if (this->base_ > destination.base_) {
                for (ptrdiff_t i = 0; i < this->size_; ++i) {
                    *reinterpret_cast<uint8_t*>(destination.base_ + i) = *reinterpret_cast<uint8_t*>(this->base_ + i);
                }
            } else {
                for (ptrdiff_t i = this->size_ -1; i >= 0; --i) {
                    *reinterpret_cast<uint8_t*>(destination.base_ + i) = *reinterpret_cast<uint8_t*>(this->base_ + i);
                }
            }
            return status_t::success;
        };
        
        inline auto copy_to(memory_t&& destination) -> status_t {
            if (this->size_ != destination.size_) return status_t::size_mismatch;
            if (this->base_ == destination.base_) return status_t::success;

            if (this->base_ > destination.base_) {
                for (ptrdiff_t i = 0; i < this->size_; ++i) {
                    *reinterpret_cast<uint8_t*>(destination.base_ + i) = *reinterpret_cast<uint8_t*>(this->base_ + i);
                }
            } else {
                for (ptrdiff_t i = this->size_ -1; i >= 0; --i) {
                    *reinterpret_cast<uint8_t*>(destination.base_ + i) = *reinterpret_cast<uint8_t*>(this->base_ + i);
                }
            }
            return status_t::success;
        };

        template <typename T>
        inline auto fill(const T value) -> status_t {
            if (this->size_ % sizeof(T)) return status_t::size_mismatch;
            for (size_t i = 0; i < this->size_; i += sizeof(T)) {
                *reinterpret_cast<T*>(this->base_ + i) = value;
            }
            return status_t::success;
        };

        inline auto subrange(ptrdiff_t offset, size_t length) -> memory_t {
            // if (offset> 0 && offset < size && (offset + length) <= size)
            return memory_t(base_ + offset, length);
        }

        inline auto clear() -> status_t {
            return fill(uint8_t(0));
        };

        inline auto size() -> size_t { return size_; }
        inline auto base() -> uintptr_t { return base_; }
        inline auto voidptr() -> void* { return reinterpret_cast<void*>(base_); }

        template <typename T>
        inline auto ref() -> T& { return *reinterpret_cast<T*>(base_); }



    };

    constexpr auto operator ""_KiB(unsigned long long value) -> size_t {
        return value * 1024;
    };

    constexpr auto operator ""_MiB(unsigned long long value) -> size_t {
        return value * 1024 * 1024;
    };

    constexpr auto operator ""_GiB(unsigned long long value) -> size_t {
        return value * 1024 * 1024 * 1024;
    };

}

inline auto operator new (size_t count, void* ptr) -> void*
{ return ptr; }
