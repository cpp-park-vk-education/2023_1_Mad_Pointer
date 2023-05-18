#pragma once
#include "../game_objects_spawn/spawn.h"
class SpawnComponent : public ecs::Component<SpawnComponent> {
private:
    Spawn m_Spawn;
public:

    SpawnComponent(const Spawn& spawn);
    virtual ~SpawnComponent();

    inline Spawn& GetSpawn() { return this->m_Spawn; }

};
