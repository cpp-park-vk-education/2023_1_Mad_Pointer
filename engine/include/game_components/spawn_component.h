#ifndef MY_PROJECT_SPAWN_COMPONENT_H
#define MY_PROJECT_SPAWN_COMPONENT_H
#include "../game_objects_spawn/spawn.h"
class SpawnComponent : public ecs::Component<SpawnComponent> {
private:
    Spawn m_Spawn;
public:

    SpawnComponent(const Spawn& spawn);
    virtual ~SpawnComponent();

    inline Spawn& GetSpawn() { return this->m_Spawn; }

};
#endif //MY_PROJECT_SPAWN_COMPONENT_H
