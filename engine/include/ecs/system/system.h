#include "system_base.h"
#include "../../utils/family_type_id.h"
#include <typeinfo>
namespace ecs {
    template<typename SystemType>
    class System : public SystemBase {
    public:
        virtual ~System() {}
        virtual const SystemTypeId getStaticSystemTypeID() const {
            return STATIC_SYSTEM_TYPE_ID;
        }

        virtual std::string getSystemTypeName() const override {
            static std::string SYSTEM_TYPE_NAME { typeid(SystemType).name() };
            return SYSTEM_TYPE_NAME;
        }

        template<class... Dependencies>
        void addDependencies(Dependencies&&... dependencies) {
            this->m_SystemManagerInstance->addSystemDependency(this, std::forward<Dependencies>(dependencies)...);
        }

        virtual void preUpdate(float deltaTime) override {}

        virtual void update(float deltaTime) override {}

        virtual void postUpdate(float deltaTime) override {}

    protected:

        System() {}
        SystemManager* m_SystemManagerInstance;
    private:

        static const SystemTypeId STATIC_SYSTEM_TYPE_ID;

    };

    template<class SystemType>
    const SystemTypeId System<SystemType>::STATIC_SYSTEM_TYPE_ID = ecs::utils::internal::FamilyTypeId<SystemBase>::get<SystemType>();
}