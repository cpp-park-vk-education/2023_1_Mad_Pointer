#pragma once
#include "allocator/stack_allocator.h"
#include <vector>
#include <list>

namespace ecs::memory::internal {
    class MemoryManager {
        friend class GlobalMemoryUser;
        using StackAllocator = allocator::StackAllocator;
    public:
        static constexpr size_t MEMORY_CAPACITY = 1;
    private:
        void* m_GlobalMemory;
        StackAllocator*	m_MemoryAllocator;
        std::vector<std::pair<const char*, void*>>	m_PendingMemory;

        std::list<void*> m_FreedMemory;
        MemoryManager(const MemoryManager&) = delete;
        MemoryManager& operator=(MemoryManager&) = delete;

    public:
        MemoryManager();
        ~MemoryManager();
        inline void* Allocate(size_t memSize, const char* user = nullptr) {}
        inline void Free(void* pMem) {}
        void CheckMemoryLeaks();
    };
}