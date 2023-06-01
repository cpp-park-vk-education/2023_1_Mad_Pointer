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
    ~RenderSystem() override {
    //    unregisterEventCallbacks();
    }

    void preUpdate(float dt) override {
        if (!m_window.isOpen()) return;
        for (auto& renderable : m_renderable) {
            if (m_killedObjects.count(renderable.getEID()))  {
                renderable.setActive(false);
            }
        }
        m_killedObjects.clear();
    }
    void update(float dt) override {
        if (!m_window.isOpen()) return;
        for (auto& renderable_object : m_renderable) {
            if (renderable_object && m_window.isOpen()) {
                renderable_object.render(m_window);
            }
        }
    }
    void postUpdate(float dt) override {
        if (!m_window.isOpen()) return;
        m_window.display();
    }

    struct Renderable {
    public:
        Renderable(ecs::EntityBase* entity, TransformComponent* transform, ShapeComponent* shape) :
                m_entityId(entity->getEntityId()),
                m_entity(entity),
                m_transformComponent(transform),
                m_shapeComponent(shape) {}

        ~Renderable() = default;

        void render(sf::RenderWindow& window) {
            m_shapeComponent->render(window, m_transformComponent->getPosition());
        }

        ecs::EntityId getEID() const {
            return m_entityId;
        }

        explicit operator bool() const {
            if (m_entity) {
                return m_isActive;
            }
            return false;
        }

        void setActive(bool active) {
            m_isActive = active;
        }

    private:
        bool m_isActive = true;
        ecs::EntityId m_entityId;
        ecs::EntityBase* m_entity;

        TransformComponent*	m_transformComponent;
        ShapeComponent*	m_shapeComponent;
    };

    using RenderableVector = std::vector<Renderable>;
private:

    void registerEventCallbacks() {
        registerEventCallback(&RenderSystem::onCarCreated);
        registerEventCallback(&RenderSystem::onGameQuitEvent);
        registerEventCallback(&RenderSystem::onGameObjectDestroyed);
        registerEventCallback(&RenderSystem::onWallCreated);
        registerEventCallback(&RenderSystem::onGameObjectCreated);
        registerEventCallback(&RenderSystem::onGameObjectDestroyed);
    }

    void onGameQuitEvent(const GameQuitEvent* event) {
        m_window.close();
    }

    void onGameObjectCreated(const GameObjectCreated* event) {
        auto entity = getEngine()->getEntityManager()->getEntity(event->m_EntityID);
        if (!entity) return;
        auto transform = entity->getComponent<TransformComponent>();
        auto shape = entity->getComponent<ShapeComponent>();

        registerRenderable(entity, transform, shape);
    }

    void onCarCreated(const CarCreated* event) {
        auto entity = getEngine()->getEntityManager()->getEntity(event->m_EntityID);
        if (!entity) return;
        auto transform = entity->getComponent<TransformComponent>();
        auto shape = entity->getComponent<ShapeComponent>();

        registerRenderable(entity, transform, shape);
    }

    void onWallCreated(const WallCreated* event) {
        GameObjectCreated e(event->m_EntityID, 0);
        onGameObjectCreated(&e);
    }

    void onGameObjectDestroyed(const GameObjectDestroyed* event) {
        unregisterRenderable(event->m_EntityID);
    }

    void onWallDestroyed(const WallDestroyed* event) {
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
