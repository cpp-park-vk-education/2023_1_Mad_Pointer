#pragma once

#include "system_manager.h"
#include "family_type_id.h"

namespace ecs {
    template<typename SystemType>
    class System : public SystemBase {
    public:
        ~System() override { /* log system init here */ }
        const SystemTypeId getStaticSystemTypeId() const override {
            return STATIC_SYSTEM_TYPE_ID;
        }

        std::string getSystemTypeName() const override {
            static std::string SYSTEM_TYPE_NAME { typeid(SystemType).name() };
            return SYSTEM_TYPE_NAME;
        }

        template<class... Dependencies>
        void addDependencies(Dependencies&&... dependencies) {
            m_SystemManagerInstance->AddSystemDependency(this, std::forward<Dependencies>(dependencies)...);
        }

        void preUpdate(float deltaTime) override {}

        void update(float deltaTime) override {}

        void postUpdate(float deltaTime) override {}

    protected:

        System() = default;
    private:
        friend class SystemManager;
        SystemManager* m_SystemManagerInstance{};
        static const SystemTypeId STATIC_SYSTEM_TYPE_ID;

    };

    template<class SystemType>
    const SystemTypeId System<SystemType>::STATIC_SYSTEM_TYPE_ID = ecs::utils::internal::FamilyTypeId<SystemBase>::get<SystemType>();
}
