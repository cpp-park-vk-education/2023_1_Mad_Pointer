#pragma once
#include "allocator/allocator_base.h"
#include "allocator/pool_allocator.h"
#include <list>

namespace ecs::memory {
    template<class OBJECT_TYPE, size_t MAX_CHUNK_OBJECTS>
    class MemoryChunkAllocator {
        static const size_t MAX_OBJECTS = MAX_CHUNK_OBJECTS;

        static const size_t ALLOC_SIZE = (sizeof(OBJECT_TYPE) + alignof(OBJECT_TYPE)) * MAX_OBJECTS;

        const char* m_AllocatorTag;

    public:

        using Allocator = memory::allocator::PoolAllocator;
        using ObjectList = std::list<OBJECT_TYPE*>;

        class MemoryChunk {
        public:
            Allocator* allocator;
            ObjectList objects;

            uintptr_t chunkStart;
            uintptr_t chunkEnd;

            MemoryChunk(Allocator* allocator) : allocator(allocator) {}

        };

        using MemoryChunks = std::list<MemoryChunk*>;

        class iterator : public std::iterator<std::forward_iterator_tag, OBJECT_TYPE> {
            typename MemoryChunks::iterator	m_CurrentChunk;
            typename MemoryChunks::iterator	m_End;

            typename ObjectList::iterator m_CurrentObject;

        public:
            iterator(typename MemoryChunks::iterator begin, typename MemoryChunks::iterator end) : m_CurrentChunk(begin), m_End(end) {}
            inline iterator& operator++() {}

            inline OBJECT_TYPE& operator*() const { return *m_CurrentObject; }
            inline OBJECT_TYPE* operator->() const { return *m_CurrentObject; }

            inline bool operator==(iterator& other) { }
            inline bool operator!=(iterator& other) {}

        };

    protected:
        MemoryChunks m_Chunks;
    public:
        MemoryChunkAllocator(const char* allocatorTag = nullptr) : m_AllocatorTag(allocatorTag){}

        virtual ~MemoryChunkAllocator() {}

        void* CreateObject() {}

        void DestroyObject(void* object) {}
        inline iterator begin() { return iterator(this->m_Chunks.begin(), this->m_Chunks.end()); }
        inline iterator end() { return iterator(this->m_Chunks.end(), this->m_Chunks.end()); }

    };
}
