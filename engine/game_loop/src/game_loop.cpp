#include "game_loop.h"
#include "render_system.h"

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
        m_window.clear();
        m_window.display();
    }
}

void GameLoop::initializeSFML() {
    m_window.create(sf::VideoMode::getDesktopMode(), m_gameName);
    if (!m_window.isOpen()) {
        LOG_ERROR("Window has not been created! Fatal!");
    }
}

void GameLoop::processWindowEvent() {
}

void GameLoop::initializeECS() {
    m_engine.getSystemManager()->AddSystem<RenderSystem>(m_window, &m_engine);
}


