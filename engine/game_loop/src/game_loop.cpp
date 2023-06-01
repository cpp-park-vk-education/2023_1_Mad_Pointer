#include "game_loop.h"

constexpr float DELTA_TIME_STEP = 1000 / 60;

void GameLoop::run() {
    sf::RectangleShape background(sf::Vector2f(1920, 1080));

    sf::Texture texture;
    if (!texture.loadFromFile(m_pathToBackground)) exit(1);
    background.setTexture(&texture);
    while (m_window.isOpen()) {
        m_engine.update(DELTA_TIME_STEP);
        if (!m_window.isOpen()) break;
        m_window.clear();
        m_window.draw(background);
    }
}

void GameLoop::initializeSFML() {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    m_window.create(sf::VideoMode::getDesktopMode(), m_gameName, sf::Style::Default, settings);

    m_window.setFramerateLimit(60);
    m_window.setMouseCursorVisible(true);
    m_window.setVerticalSyncEnabled(true);
    m_window.setActive(true);

    m_window.requestFocus();
    if (!m_window.isOpen()) {
        LOG_ERROR("Window has not been created! Fatal!");
    }
}
