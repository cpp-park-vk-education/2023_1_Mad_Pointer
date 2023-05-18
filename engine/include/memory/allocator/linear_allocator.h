#pragma once
#include "allocator_base.h"
namespace ecs::memory::allocator {
    class LinearAllocator : public AllocatorBase {
    public:
        LinearAllocator(size_t memSize, const void* mem);

        virtual ~LinearAllocator();

        virtual void *allocate(size_t size, u_int8_t alignment) override;

        virtual void free(void *p) override;

        virtual void clear() override;

    };
}