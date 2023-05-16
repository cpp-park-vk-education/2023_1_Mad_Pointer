#ifndef MY_PROJECT_RESPAWN_COMPONENT_H
#define MY_PROJECT_RESPAWN_COMPONENT_H
class RespawnComponent : public ecs::Component<RespawnComponent> {
public:

    bool m_AutoRespawn;
    float m_RespawnTime;
    Position m_RespawnPosition;
    glm::vec3 m_RespawnOrientation;
    GameObjectId m_SpawnId;

    RespawnComponent(float respawnTime, const GameObjectId spawnId, bool autoRespawn = false) :
            m_AutoRespawn(autoRespawn),
            m_RespawnTime(respawnTime),
            m_RespawnPosition(INVALID_POSITION),
            m_RespawnOrientation(0.0f),
            m_SpawnId(spawnId) {}

    RespawnComponent(float respawnTime, bool autoRespawn = false, const Position& respawnPosition = INVALID_POSITION, const glm::vec3& respawnOrientation = glm::vec3(0.0f)) :
            m_AutoRespawn(autoRespawn),
            m_RespawnTime(respawnTime),
            m_RespawnPosition(respawnPosition),
            m_RespawnOrientation(respawnOrientation),
            m_SpawnId(INVALID_GAMEOBJECT_ID) {}
};
#endif //MY_PROJECT_RESPAWN_COMPONENT_H
