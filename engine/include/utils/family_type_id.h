#pragma once
#include <iostream>
namespace ecs::utils::internal {
    using TypeId = size_t;
    template<typename ClassType>
    class FamilyTypeId {
    public:

        template<class NewClass>
        static TypeId get() {
            static const TypeId staticTypeId{m_typeCount++};
            return staticTypeId;
        }

        static TypeId get() {
            return m_typeCount;
        }
    private:
        static TypeId m_typeCount;
    };


}