#ifndef INC_2023_1_MAD_POINTER_COMPONENT_H
#define INC_2023_1_MAD_POINTER_COMPONENT_H

#endif //INC_2023_1_MAD_POINTER_COMPONENT_H


class Player: Entity {
public:
    Player(...) m_transformComponent(this, m_spawnPosition), m_respawnComponent(this, m_timeToRespawn, isAlive) {}

private:
    TransformComponent* m_transformComponent;
    RespawnComponent* m_respawnComponent;
    ...
};