#pragma once
#include "event_listener.h"
#include "game_event.h"
#include "transform_component.h"
#include "projectile.h"

const int PLAYER_SPEED = 10;

class Controller : public ecs::event::EventListenerBase {
public:
    Controller(ecs::Engine* engine) : ecs::event::EventListenerBase(engine), m_engine(engine) {
        registerEventCallbacks();
    }

    ~Controller() override {
        //unregisterEventCallbacks();
    }

    void setTransform(TransformComponent* transform) {
        m_transform = transform;
    }

private:
    void registerEventCallbacks() {
        registerEventCallback(&Controller::onButtonPressed);
        registerEventCallback(&Controller::onButtonReleased);
        registerEventCallback(&Controller::onMouseButtonPressed);
    }

    void onButtonPressed(const KeyPressedEvent* event) {
        switch (event->keyCode) {
            case sf::Keyboard::A:
                m_transform->setAngle(180);
                m_transform->setSpeed(PLAYER_SPEED);
                break;
            case sf::Keyboard::D:
                m_transform->setAngle(0);
                m_transform->setSpeed(PLAYER_SPEED);
                break;
            case sf::Keyboard::S:
                m_transform->setAngle(90);
                m_transform->setSpeed(PLAYER_SPEED);
                break;
            case sf::Keyboard::W:
                m_transform->setAngle(270);
                m_transform->setSpeed(PLAYER_SPEED);
                break;
        }
    }

    void onButtonReleased(const KeyReleasedEvent* event) {
        if (event->keyCode == sf::Keyboard::A || event->keyCode == sf::Keyboard::D
            || event->keyCode == sf::Keyboard::S || event->keyCode == sf::Keyboard::W) {
            m_transform->setSpeed(0);
        }
    }

    void onMouseButtonPressed(const LeftMouseButtonPressed* event) {
        m_engine->getEntityManager()->CreateEntity<Projectile>(m_engine, m_engine->getComponentManager(), m_transform->getPosition(), 20, m_transform->getAngle());
    }

    void unregisterEventCallbacks() {
        unregisterEventCallback(&Controller::onButtonPressed);
        unregisterEventCallback(&Controller::onButtonReleased);
        unregisterEventCallback(&Controller::onMouseButtonPressed);
    }

private:
    TransformComponent* m_transform;
    ecs::Engine* m_engine;
};
