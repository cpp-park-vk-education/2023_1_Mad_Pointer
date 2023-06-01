#pragma once
#include "event_listener.h"
#include "game_event.h"
#include "transform_component.h"
#include "projectile.h"

const int CAR_SPEED = 10;

class CarController : public ecs::event::EventListenerBase {
public:
    CarController(ecs::Engine* engine) : ecs::event::EventListenerBase(engine), m_engine(engine) {
        registerEventCallbacks();
    }

    ~CarController() override {
        //unregisterEventCallbacks();
    }

    void setTransform(TransformComponent* transform) {
        m_transform = transform;
    }

private:
    void registerEventCallbacks() {
        registerEventCallback(&CarController::onButtonPressed);
        registerEventCallback(&CarController::onButtonReleased);
        registerEventCallback(&CarController::onMouseButtonPressed);
    }

    void onButtonPressed(const KeyPressedEvent* event) {
        switch (event->keyCode) {
            case sf::Keyboard::A:
                m_transform->setAngle(180);
                m_transform->setSpeed(CAR_SPEED);
                break;
            case sf::Keyboard::D:
                m_transform->setAngle(0);
                m_transform->setSpeed(CAR_SPEED);
                break;
        }
    }

    void onButtonReleased(const KeyReleasedEvent* event) {
        if (event->keyCode == sf::Keyboard::A || event->keyCode == sf::Keyboard::D) {
            m_transform->setSpeed(0);
        }
    }

    void onMouseButtonPressed(const LeftMouseButtonPressed* event) {
    }

    void unregisterEventCallbacks() {
        unregisterEventCallback(&CarController::onButtonPressed);
        unregisterEventCallback(&CarController::onButtonReleased);
        unregisterEventCallback(&CarController::onMouseButtonPressed);
    }

private:
    TransformComponent* m_transform;
    ecs::Engine* m_engine;
};
