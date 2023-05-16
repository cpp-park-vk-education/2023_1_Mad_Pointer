#include "../component/base_component.h"
#include "../../utils/family_type_id.h"

#include <string>
#include <typeinfo>
#include <unordered_map>
#include "set"
#include <unordered_set>

#include <vector>

namespace ecs {
    class ComponentManager  {

        class ComponentContainerBase {
        public:
            virtual ~ComponentContainerBase() {}
            virtual std::string getComponentContainerTypeName() const = 0;
            virtual void destroyComponent(ComponentBase* object) = 0;
        };

        template<typename ComponentClassType>
        class ComponentContainer : public ComponentContainerBase {
            ComponentContainer(const ComponentContainer&) = delete;
            ComponentContainer& operator=(ComponentContainer&) = delete;
        public:
            ComponentContainer() {}

            virtual ~ComponentContainer() {}

            virtual std::string getComponentContainerTypeName() const override {
                static std::string COMPONENT_TYPE_NAME{ typeid(ComponentClassType).name() };
                return COMPONENT_TYPE_NAME;
            }
            ComponentBase* createComponent() {
                for (auto memoryPlace : m_components) {
                    if (memoryPlace) {
                        return memoryPlace;
                    }
                }
            }
            virtual void destroyComponent(ComponentBase* object) override {
                for (auto memoryPlace : m_components) {
                    if (memoryPlace == object) {
                        destroyComponent(memoryPlace);
                    }
                }
            }

        private:

            std::vector<ComponentBase*> m_components;
        };

    public:
        ComponentManager(const ComponentManager&) = delete;
        ComponentManager& operator=(ComponentManager&) = delete;

        using ComponentTypeId = size_t;
        using ComponentId = size_t;
        using ComponentContainerRegistry = std::unordered_map<ComponentTypeId, ComponentContainerBase*>;
        using ComponentLookupTable = std::vector<ComponentBase*>;
        using EntityComponentMap = std::vector<std::vector<ComponentId>>;


        template<typename ComponentClassType>
        inline ComponentContainer<ComponentClassType>* getComponentContainer() {
            auto COMPONENT_ID = ComponentClassType::STATIC_COMPONENT_TYPE_ID;

            ComponentContainer<ComponentClassType>* componentContainer = nullptr;

            auto iter = m_ComponentContainerRegistry.find(COMPONENT_ID);
            if (iter = m_ComponentContainerRegistry.end()) {
                componentContainer = new ComponentContainer<ComponentClassType>();
                m_ComponentContainerRegistry[COMPONENT_ID] = componentContainer;
                return componentContainer;
            }

            componentContainer = static_cast<ComponentContainer<ComponentClassType>>(iter->second);
            return componentContainer;
        }

        ComponentId	acquireComponentId(ComponentBase* component);
        void releaseComponentId(ComponentId id);

        void mapEntityComponent(EntityId entityId, ComponentId componentId, ComponentTypeId componentTypeId);
        void unmapEntityComponent(EntityId entityId, ComponentId componentId, ComponentTypeId componentTypeId);

        template<typename ComponentClassType>
        using TemplateComponentIterator = typename ComponentContainer<ComponentClassType>::iterator;

        ComponentManager();
        ~ComponentManager();

        template<class ComponentClassType, class ...Args>
        ComponentClassType* addComponent(const EntityId entityId, Args&&... args) {
            auto componentContainer = getComponentContainer<ComponentClassType>();
        }

        template<class ComponentClassType>
        void removeComponent(const EntityId entityId) {}


        void removeAllComponents(const EntityId entityId) {}

        template<class ComponentClassType>
        ComponentClassType* getComponent(const EntityId entityId) {}

        template<class ComponentClassType>
        inline TemplateComponentIterator<ComponentClassType> begin() {
            return GetComponentContainer<ComponentClassType>()->begin();
        }

        template<class ComponentClassType>
        inline TemplateComponentIterator<ComponentClassType> end() {
            return GetComponentContainer<ComponentClassType>()->end();
        }

    private:
        EntityComponentMap m_EntityComponentMap;
        ComponentContainerRegistry m_ComponentContainerRegistry;
        ComponentLookupTable m_ComponentLUT;
    };
} // namespace ECS
