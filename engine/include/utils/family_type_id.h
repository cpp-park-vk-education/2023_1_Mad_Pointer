#pragma once
#include <iostream>
namespace ecs::utils::internal {
    using TypeId = size_t;
    template<typename ClassType>
    class FamilyTypeId {
    public:

        template<class NewClass>
        static const TypeId get() {
            static const TypeId STATIC_TYPE_ID{m_typeCount++};
            return STATIC_TYPE_ID;
        }

        static const TypeId get() {
            return m_typeCount;
        }
    private:
        static TypeId m_typeCount;
    };


}