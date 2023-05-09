#include <vector>
#include <unordered_map>
class SystemRegistry {
public:
    void update(float deltaTime);
    void addSystem(System system);
    void registerSystemWithComponent();
private:
    std::vector<System> m_systems;


};

class Scene {
public:
    virtual

private:
    std::unordered_map<size_t, Entity> m_roomToEntity;
};

class FloorScene {

};