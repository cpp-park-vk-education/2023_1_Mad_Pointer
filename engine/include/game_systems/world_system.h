#pragma once
#include <vector>
class WorldSystem {
    struct SpawnInfo {
        GameObjectId m_GameObjectID;
        Transform m_Transform;

        SpawnInfo() : m_GameObjectID(INVALID_GAMEOBJECT_ID), m_Transform(Transform()) {}

        SpawnInfo(GameObjectId gameObjectId, const Transform& transform) : m_GameObjectID(gameObjectId), m_Transform(transform) {}
    };

    struct WorldObjectInfo {
        GameObjectId m_GameObjectID;
        EntityTypeId m_GameObjectType;

        WorldObjectInfo() : m_GameObjectID(INVALID_GAMEOBJECT_ID), m_GameObjectType(INVALID_TYPE_ID) {}

        WorldObjectInfo(GameObjectId objectId, EntityTypeId typeId) : m_GameObjectID(objectId), m_GameObjectType(typeId) {}

    };

    using SpawnQueue = std::vector<SpawnInfo>;
    using KillQueue	= std::vector<GameObjectId>;

    using WorldObjects = std::vector<WorldObjectInfo>;

private:
    b2World	m_Box2DWorld;

    WorldObjects m_WorldObjects;
    SpawnQueue m_SpawnQueue;
    size_t m_PendingSpawns;

    KillQueue m_KillQueue;
    size_t m_PendingKills;

public:

    WorldSystem();
    virtual ~WorldSystem();

    void PreUpdate(float dt);
    void Update(float dt);
    void PostUpdate(float dt);

    void SpawnGameObject(GameObjectId gameObjectId, const Transform& transform);

    void KillGameObject(GameObjectId gameObjectId);

    void RemoveGameObject(GameObjectId gameObjectId);

    void Clear();

    template<class T, class... ARGS>
    GameObjectId AddGameObject(Transform transform, ARGS&&... args) {}

    template<class T>
    T* GetGameObject(const GameObjectId& objectId) {}

    inline b2World* GetBox2dWorld() {}

    template<class T>
    void KillAllGameObjects() {}

    void KillAllGameObjects() {}

    void DumpPhysics() {}
};
