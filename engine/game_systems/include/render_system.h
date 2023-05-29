#pragma once
#include "system.h"
#include "entity_base.h"
#include "game_event.h"
#include "event_listener.h"
#include "shape_component.h"
#include "transform_component.h"
#include <SFML/Graphics.hpp>

class RenderSystem : public ecs::System<RenderSystem>, public ecs::event::EventListenerBase {
public:
    RenderSystem(sf::RenderWindow& window, ecs::Engine* engine) : m_window(window), ecs::event::EventListenerBase(engine) {
        registerEventCallbacks();
    }
    ~RenderSystem() override { unregisterEventCallbacks(); }

    void preUpdate(float dt) override {}
    void update(float dt) override {
        for (auto& renderable_object : m_renderable) {
            if (renderable_object) {
                renderable_object.render(m_window);
            }
        }
        m_window.display();
    }
    void postUpdate(float dt) override {}

    struct Renderable {
    public:
        Renderable(ecs::EntityBase* entity, TransformComponent* transform, ShapeComponent* shape) :
                m_entityTypeId(entity->getStaticEntityTypeId()),
                m_entity(entity),
                m_transformComponent(transform),
                m_shapeComponent(shape) {}

        ~Renderable() = default;

        void render(sf::RenderWindow& window) {
            m_shapeComponent->render(window, m_transformComponent->getPosition());
        }

        explicit operator bool() const {
            if (m_entity) {
                return m_entity->isActive();
            }
            return false;
        }

    private:
        [[maybe_unused]] ecs::EntityTypeId m_entityTypeId;
        ecs::EntityBase* m_entity;

        TransformComponent*	m_transformComponent;
        ShapeComponent*	m_shapeComponent;
    };

    using RenderableVector = std::vector<Renderable>;
private:

    [[maybe_unused]] void registerEventCallbacks() {
        registerEventCallback(&RenderSystem::onGameObjectCreated);
        registerEventCallback(&RenderSystem::onGameObjectDestroyed);
    }

    void onGameObjectCreated(const GameObjectCreated* event) {
        auto entity = getEngine()->getEntityManager()->getEntity(event->m_EntityID);
        auto transform = getEngine()->getComponentManager()->getComponent<TransformComponent>(event->m_EntityID);
        auto shape = getEngine()->getComponentManager()->getComponent<ShapeComponent>(event->m_EntityID);

        registerRenderable(entity, transform, shape);
    }

    void onGameObjectDestroyed(const GameObjectDestroyed* event) {
        unregisterRenderable(event->m_EntityID);
    }

    [[maybe_unused]] void unregisterEventCallbacks() {
        unregisterEventCallback(&RenderSystem::onGameObjectCreated);
        unregisterEventCallback(&RenderSystem::onGameObjectDestroyed);
    }

    void registerRenderable(ecs::EntityBase* entity, TransformComponent* transform, ShapeComponent* shape) {
        m_renderable.emplace_back(entity, transform, shape);
    }

    void unregisterRenderable(ecs::EntityId gameObjectId) {
        m_killedObjects.insert(gameObjectId);
    }

    sf::RenderWindow& m_window;
    RenderableVector m_renderable;
    std::unordered_set<ecs::EntityId> m_killedObjects;
};
