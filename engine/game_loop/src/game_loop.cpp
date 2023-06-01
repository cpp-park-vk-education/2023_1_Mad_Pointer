#include "game_loop.h"
#include "render_system.h"
#include "collision_system.h"
#include "transform_system.h"
#include "enemy_controller_system.h"
#include "spawn_system.h"
#include "player.h"
#include "input_system.h"
#include "wall.h"

constexpr float DELTA_TIME_STEP = 1000 / 60;

void GameLoop::run() {
    sf::RectangleShape background(sf::Vector2f(1920, 1080));

    sf::Texture texture;
    if (!texture.loadFromFile("image/image.jpg")) exit(1);
    background.setTexture(&texture);
    while (m_window.isOpen()) {
        m_engine.update(DELTA_TIME_STEP);
        if (!m_window.isOpen()) break;
        m_window.clear();
        m_window.draw(background);
    }
}

void GameLoop::initializeSFML() {
    m_window.create(sf::VideoMode::getDesktopMode(), m_gameName);

    m_window.setFramerateLimit(60);
    m_window.setMouseCursorVisible(true);
    m_window.setVerticalSyncEnabled(true);
    m_window.setActive(true);
    m_window.requestFocus();
    if (!m_window.isOpen()) {
        LOG_ERROR("Window has not been created! Fatal!");
    }
}

void GameLoop::initializeECS() {
    m_engine.getSystemManager()->AddSystem<RenderSystem>(m_window, &m_engine);
    m_engine.getSystemManager()->AddSystem<InputSystem>(m_window, &m_engine);
    m_engine.getSystemManager()->AddSystem<TransformSystem>(&m_engine);
    m_engine.getSystemManager()->AddSystem<SpawnSystem>(&m_engine);
    m_engine.getSystemManager()->AddSystem<CollisionSystem>(&m_engine);
    m_engine.getSystemManager()->AddSystem<EnemyControllerSystem>(&m_engine);

    m_engine.getEntityManager()->CreateEntity<Player>(&m_engine, m_engine.getComponentManager(), sf::Vector2f{200, 200});

    std::vector<sf::Vector2f> verticesForWall = {{10, 10}, {10, 990}, {1800, 990}, {1800, 10}, {10, 10}};
    m_engine.getEntityManager()->CreateEntity<Wall>(&m_engine, m_engine.getComponentManager(), verticesForWall);
}
