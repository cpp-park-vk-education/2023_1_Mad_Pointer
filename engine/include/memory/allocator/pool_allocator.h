#include "allocator_base.h"

namespace ecs::memory::allocator {

    class PoolAllocator : public AllocatorBase {
    private:

        const size_t OBJECT_SIZE;
        const uint8_t OBJECT_ALIGNMENT;
        void** freeList;

    public:
        PoolAllocator(size_t memSize, const void* mem, size_t objectSize, uint8_t objectAlignment);
        virtual ~PoolAllocator();
        virtual void* allocate(size_t size, uint8_t alignment) override;
        virtual void free(void* p) override;
        virtual void clear() override;

    };

}