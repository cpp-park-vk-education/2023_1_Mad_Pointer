#include "game_loop.h"
#include "render_system.h"
#include "player.h"
#include "enemy.h"

constexpr float DELTA_TIME_STEP = 1000 / 60;

void GameLoop::run() {
    while (m_window.isOpen()) {
        for (auto event = sf::Event{}; m_window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                m_window.close();
            }
        }

        m_engine.update(DELTA_TIME_STEP);
    }
}

void GameLoop::initializeSFML() {
    m_window.create(sf::VideoMode::getDesktopMode(), m_gameName);
    m_window.setFramerateLimit(60);
    m_window.setMouseCursorVisible(true);
    m_window.setVerticalSyncEnabled(true);
    if (!m_window.isOpen()) {
        LOG_ERROR("Window has not been created! Fatal!");
    }

    //sf::RenderWindow window(sf::VideoMode(600, 600), m_gameName);
    sf::CircleShape circleShape(100, 30);
    circleShape.setRadius(30);
    circleShape.setFillColor(sf::Color::White);
    circleShape.setPosition(50, 50);
    //for (int i = 0; i < 1000; ++i) {
    //    m_window.draw(circleShape);
    //        m_window.display();
    //}
}

void GameLoop::processWindowEvent() {
}

void GameLoop::initializeECS() {
    m_engine.getSystemManager()->AddSystem<RenderSystem>(m_window, &m_engine);
    m_engine.getEntityManager()->CreateEntity<Enemy>(&m_engine, m_engine.getComponentManager(), sf::Vector2f(50, 50));
    m_engine.getEntityManager()->CreateEntity<Enemy>(&m_engine, m_engine.getComponentManager(), sf::Vector2f(70, 70));

    m_engine.getEntityManager()->CreateEntity<Enemy>(&m_engine, m_engine.getComponentManager(), sf::Vector2f(120, 90));


    m_engine.getEntityManager()->CreateEntity<Player>(&m_engine, m_engine.getComponentManager(), sf::Vector2f{10, 10});
    m_engine.getEntityManager()->CreateEntity<Player>(&m_engine, m_engine.getComponentManager(), sf::Vector2f{30, 30});

}


