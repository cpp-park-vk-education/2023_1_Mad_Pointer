#pragma once
#include "system.h"
#include "entity_base.h"
#include "game_event.h"
#include "event_listener.h"
#include "transform_component.h"
#include "projectile.h"
#include <SFML/Graphics.hpp>

class ScoreSystem : public ecs::System<ScoreSystem>, public ecs::event::EventListenerBase {
public:
    explicit ScoreSystem(sf::RenderWindow& window, ecs::Engine* engine) : m_window(window), m_engine(engine), ecs::event::EventListenerBase(engine), m_score(0) {
        registerEventCallbacks();
        
        if (!font.loadFromFile("font/MyriadPro.otf")) { exit(1); }
        text.setFont(font);
        text.setPosition(50, 50);
        text.setString("Score: " + std::to_string(m_score));
        text.setCharacterSize(40);
        text.setFillColor(sf::Color::White);
    }

    ~ScoreSystem() override {
        //unregisterEventCallbacks();
    }

    void postUpdate(float dt) override {
        if (!m_window.isOpen()) return;
        text.setString("Score: " + std::to_string(m_score));
        m_window.draw(text);
    }

private:
    void registerEventCallbacks() {
        registerEventCallback(&ScoreSystem::onEnemyDestroyed);
    }

    void onEnemyDestroyed(const EnemyDestroyed* event) {
        m_score += 10;
    }

    void unregisterEventCallbacks() {
        unregisterEventCallback(&ScoreSystem::onEnemyDestroyed);
    }

private:
    sf::RenderWindow& m_window;
    ecs::Engine* m_engine;
    int m_score;
    sf::Text text;
    sf::Font font;
};
