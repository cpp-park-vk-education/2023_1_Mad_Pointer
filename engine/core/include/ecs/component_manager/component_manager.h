#pragma once
#include "base_component.h"
#include "family_type_id.h"

#include <string>
#include <typeinfo>
#include <unordered_map>
#include <unordered_set>
#include <memory>
#include <vector>

namespace ecs {
    class ComponentManager  {
        friend class ComponentBase;
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
            ComponentBase* createComponent(ComponentId compId, std::shared_ptr<ComponentClassType> component) {
                m_components[compId] = component;
                return m_components.at(compId).get();
            }

            virtual void destroyComponent(ComponentBase* object) override {
                del(object->getComponentId());
            }

            ComponentBase* getComponent(ComponentId componentId) const {
                return m_components.at(componentId);
            }

            void del(ComponentId componentId) {
                m_components.erase(componentId);
            }

        private:

            std::unordered_map<ComponentId, std::shared_ptr<ComponentClassType>> m_components;
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
            if (iter == m_ComponentContainerRegistry.end()) {
                componentContainer = new ComponentContainer<ComponentClassType>();
                m_ComponentContainerRegistry[COMPONENT_ID] = componentContainer;
                return componentContainer;
            }

            componentContainer = static_cast<ComponentContainer<ComponentClassType>*>(iter->second);
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
            auto componentTypeID = ComponentClassType::STATIC_COMPONENT_TYPE_ID;
            std::shared_ptr<ComponentClassType> component = std::make_shared<ComponentClassType>(entityId, std::forward<Args>(args)...);

            auto componentID = acquireComponentId(component.get());
            component->setOwner(entityId);
            component->setComponentId(componentID);

            componentContainer->createComponent(componentID, component);
            mapEntityComponent(entityId, componentID, componentTypeID);

            return component.get();
        }

        template<class ComponentClassType>
        void removeComponent(const EntityId entityId) {
            auto componentContainer = getComponentContainer<ComponentClassType>();
            auto componentTypeID = ComponentClassType::STATIC_COMPONENT_TYPE_ID;

            auto componentID = m_EntityComponentMap[entityId][componentTypeID];
            componentContainer->del(componentID);
            unmapEntityComponent(entityId, componentID, componentTypeID);
        }


        void removeAllComponents(EntityId entityId);

        template<class ComponentClassType>
        ComponentClassType* getComponent(const EntityId entityId) {
            auto componentTypeID = ComponentClassType::STATIC_COMPONENT_TYPE_ID;
            const ComponentId componentId = m_EntityComponentMap[entityId][componentTypeID];

            auto component = m_ComponentLUT[componentId];
            return static_cast<ComponentClassType*>(component);
        }

        template<class ComponentClassType>
        inline TemplateComponentIterator<ComponentClassType> begin() {
            return getComponentContainer<ComponentClassType>()->begin();
        }

        template<class ComponentClassType>
        inline TemplateComponentIterator<ComponentClassType> end() {
            return getComponentContainer<ComponentClassType>()->end();
        }

    private:
        EntityComponentMap m_EntityComponentMap;
        ComponentContainerRegistry m_ComponentContainerRegistry;
        ComponentLookupTable m_ComponentLUT;
    };
} // namespace ecs
