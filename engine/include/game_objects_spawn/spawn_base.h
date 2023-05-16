#ifndef MY_PROJECT_SPAWN_BASE_H
#define MY_PROJECT_SPAWN_BASE_H

struct SpawnInfo {
    Position	m_SpawnPosition;
    glm::vec3	m_SpawnOrientation;

    SpawnInfo() : m_SpawnPosition(Position(0.0f)), m_SpawnOrientation(glm::vec3(0.0f)) {}

    SpawnInfo(const Position& position, const glm::vec3& orientation) : m_SpawnPosition(position), m_SpawnOrientation(orientation) {}
};

enum RandomSpawnSampler {
    Unitform = 0,
    Spherical,
    Gaussian,
};

class SpawnBase {
public:
    SpawnBase() {}

    virtual ~SpawnBase() {}

    virtual SpawnInfo GetFixSpawnInfo() = 0;

    virtual SpawnInfo GetRelativeSpawnInfo(float uniform_x, float uniform_y, float uniform_z) = 0;

    virtual SpawnInfo SampleRandomSpawnInfo(RandomSpawnSampler sample = RandomSpawnSampler::Unitform) = 0;
};

#endif //MY_PROJECT_SPAWN_BASE_H
