#pragma once
#include "spawn_base.h"
class PointSpawn : public SpawnBase {
private:

    Position m_SpawnPosition;
    glm::vec2 m_SpawnOrientation;

public:

    PointSpawn(const Position& position, const glm::vec3& orientation = glm::vec3(0.0f));
    virtual ~PointSpawn();

    virtual SpawnInfo GetFixSpawnInfo() override;
    virtual SpawnInfo GetRelativeSpawnInfo(float uniform_x, float uniform_y, float uniform_z) override;
    virtual SpawnInfo SampleRandomSpawnInfo(RandomSpawnSampler sample = RandomSpawnSampler::Unitform) override;

};
