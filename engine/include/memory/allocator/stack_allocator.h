#pragma once
#include "allocator_base.h"
namespace ecs::memory::allocator {
    class  StackAllocator : public AllocatorBase {
    public:
        StackAllocator(size_t memSize, const void* mem);
        virtual ~StackAllocator();
        virtual void* allocate(size_t size, uint8_t alignment) override;
        virtual void free(void* p) override;
        virtual void clear() override;
    private:
        struct AllocMetaInfo {
            uint8_t adjustment;
        };

    };
}
