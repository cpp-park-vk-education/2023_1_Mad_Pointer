#include "game_loop.h"
#include "render_system.h"
#include "collision_system.h"
#include "transform_system.h"
#include "enemy_controller_system.h"
#include "spawn_system.h"
#include "player.h"
#include "input_system.h"
#include "wall.h"
#include "score_system.h"

class GameLoopShooter : public GameLoop {
public:
    GameLoopShooter(const std::string& gameName, const std::string& pathToBackground) : GameLoop(gameName, pathToBackground) {}
    void initializeECS() override {
        m_engine.getSystemManager()->AddSystem<ScoreSystem>(m_window, &m_engine);
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
};
