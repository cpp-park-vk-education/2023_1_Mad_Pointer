#include "../component/base_component.h"
#include <string>
#include <typeinfo>
#include <unordered_map>
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

            virtual void destroyComponent(ComponentBase* object) override {
                object->~ComponentBase();
                this->destroyObject(object);
            }

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
        inline ComponentContainer<ComponentClassType>* getComponentContainer() {}

        ComponentId	acquireComponentId(ComponentBase* component);
        void releaseComponentId(ComponentId id);

        void mapEntityComponent(EntityId entityId, ComponentId componentId, ComponentTypeId componentTypeId);
        void unmapEntityComponent(EntityId entityId, ComponentId componentId, ComponentTypeId componentTypeId);

        template<typename ComponentClassType>
        using TemplateComponentIterator = typename ComponentContainer<ComponentClassType>::iterator;

        ComponentManager();
        ~ComponentManager();

        template<class ComponentClassType, class ...Args>
        ComponentClassType* addComponent(const EntityId entityId, Args&&... args) {}

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
