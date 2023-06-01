#pragma once
#include "game_loop.h"
#include "render_system.h"
#include "rectangle_collision_system.h"
#include "transform_system.h"
#include "enemy_controller_system.h"
#include "car_spawn_system.h"
#include "car.h"
#include "box.h"
#include "input_system.h"
#include "wall.h"

const int wallOffset = 1000;

class GameLoopCars : public GameLoop {
public:
    GameLoopCars(const std::string& gameName, const std::string& pathToBackground) : GameLoop(gameName, pathToBackground) {}
    void initializeECS() override {
    /*
        m_engine.getSystemManager()->AddSystem<RenderSystem>(m_window, &m_engine);
        m_engine.getSystemManager()->AddSystem<InputSystem>(m_window, &m_engine);
        m_engine.getSystemManager()->AddSystem<TransformSystem>(&m_engine);
        m_engine.getSystemManager()->AddSystem<SpawnSystem>(&m_engine);
        m_engine.getSystemManager()->AddSystem<CollisionSystem>(&m_engine);
        m_engine.getSystemManager()->AddSystem<EnemyControllerSystem>(&m_engine);

        m_engine.getEntityManager()->CreateEntity<Player>(&m_engine, m_engine.getComponentManager(), sf::Vector2f{200, 200});

        std::vector<sf::Vector2f> verticesForWall = {{10, 10}, {10, 990}, {1800, 990}, {1800, 10}, {10, 10}};
        m_engine.getEntityManager()->CreateEntity<Wall>(&m_engine, m_engine.getComponentManager(), verticesForWall);
    */

        m_engine.getSystemManager()->AddSystem<RenderSystem>(m_window, &m_engine);
        m_engine.getSystemManager()->AddSystem<InputSystem>(m_window, &m_engine);
        m_engine.getSystemManager()->AddSystem<TransformSystem>(&m_engine);
        m_engine.getSystemManager()->AddSystem<CarSpawnSystem>(&m_engine);
        m_engine.getSystemManager()->AddSystem<RectangleCollisionSystem>(&m_engine);

        m_engine.getEntityManager()->CreateEntity<Car>(&m_engine, m_engine.getComponentManager(), sf::Vector2f{200, 200}, sf::Vector2f{100, 300});

        
        float width = sf::VideoMode::getDesktopMode().width;
        float height = sf::VideoMode::getDesktopMode().height;
        
        std::vector<sf::Vector2f> verticesForWall = {{0, -wallOffset}, {0, height + wallOffset}, {width, height + wallOffset},
                                                    {width, -wallOffset}, {0, -wallOffset}};
        m_engine.getEntityManager()->CreateEntity<Wall>(&m_engine, m_engine.getComponentManager(), verticesForWall);
    }
};
