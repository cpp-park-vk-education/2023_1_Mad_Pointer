#pragma once
#include <iostream>
namespace ecs::memory::allocator {
    static inline void* AlignForward(void *address, uint8_t alignment);

    static inline uint8_t GetAdjustment(const void *address, uint8_t alignment);

    static inline uint8_t GetAdjustment(const void *address, uint8_t alignment, uint8_t extra);
    class AllocatorBase {
    protected:
        const size_t m_MemorySize;
        const void *m_MemoryFirstAddress;

        size_t m_MemoryUsed;
        uint64_t m_MemoryAllocations;

    public:
        AllocatorBase(const size_t memSize, const void *mem);

        virtual ~AllocatorBase();

        virtual void *allocate(size_t size, uint8_t alignment) = 0;

        virtual void free(void *p) = 0;

        virtual void clear() = 0;

        inline size_t GetMemorySize() const;

        inline const void *GetMemoryAddress0() const;

        inline size_t GetUsedMemory() const;

        inline uint64_t GetAllocationCount() const;
    };
}
