#include "base_component.h"

namespace ecs {
    template<typename ComponentType>
    class Component : public ComponentBase {
    public:
        ComponentTypeId getStaticComponentTypeId() const {
            return STATIC_COMPONENT_TYPE_ID;
        }

        Component() {}
        virtual ~Component();
    protected:
        static ComponentTypeId STATIC_COMPONENT_TYPE_ID; //здесь получаем идентификатор типа компонента
    private:

    };
}
