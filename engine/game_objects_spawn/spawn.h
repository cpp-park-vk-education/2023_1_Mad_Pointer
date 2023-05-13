#ifndef MY_PROJECT_SPAWN_H
#define MY_PROJECT_SPAWN_H
#include "spawn_base.h"
class Spawn {
private:

    SpawnBase* m_SpawnImpl;

public:

    Spawn(SpawnBase* spawnImpl) : m_SpawnImpl(spawnImpl) {}

    ~Spawn() {}

    void SetSpawn(SpawnBase* spawnImpl) { }

    void DeleteSpawn() {}

    inline SpawnInfo GetFixSpawnInfo() { return this->m_SpawnImpl->GetFixSpawnInfo(); }

    inline SpawnInfo GetRelativeSpawnInfo(float uniform_x, float uniform_y, float uniform_z = 0.0f) { return this->m_SpawnImpl->GetRelativeSpawnInfo(uniform_x, uniform_y, uniform_z); }

    inline SpawnInfo SampleRandomSpawnInfo(RandomSpawnSampler sample = RandomSpawnSampler::Unitform) { return this->m_SpawnImpl->SampleRandomSpawnInfo(sample); }

};
#endif //MY_PROJECT_SPAWN_H
