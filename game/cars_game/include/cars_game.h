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

        m_engine.getSystemManager()->AddSystem<ScoreSystem>(m_window, &m_engine);
        m_engine.getSystemManager()->AddSystem<RenderSystem>(m_window, &m_engine);
        m_engine.getSystemManager()->AddSystem<InputSystem>(m_window, &m_engine);
        m_engine.getSystemManager()->AddSystem<TransformSystem>(&m_engine);
        m_engine.getSystemManager()->AddSystem<CarSpawnSystem>(&m_engine);
        m_engine.getSystemManager()->AddSystem<RectangleCollisionSystem>(&m_engine);

        float width = sf::VideoMode::getDesktopMode().width;
        float height = sf::VideoMode::getDesktopMode().height;

        m_engine.getEntityManager()->CreateEntity<Car>(&m_engine, m_engine.getComponentManager(), sf::Vector2f{width / 2, height - 300}, sf::Vector2f{100, 300});
        
        std::vector<sf::Vector2f> verticesForWall = {{0, -wallOffset}, {0, height + wallOffset}, {width, height + wallOffset},
                                                    {width, -wallOffset}, {0, -wallOffset}};
        m_engine.getEntityManager()->CreateEntity<Wall>(&m_engine, m_engine.getComponentManager(), verticesForWall);
    }
};
