#include "../../../engine/ecs.h"

using GameObjectId = ECS::EntityId;
using GameObjectTypeId = ECS::EntityTypeId;

using PlayerId = size_t;

static const GameObjectId INVALID_GAMEOBJECT_ID	{ ECS::INVALID_ENTITY_ID };
static const PlayerId INVALID_PLAYER_ID	{ std::numeric_limits<PlayerId>::max() };

enum CollisionCategory {
    Default_Category = 0x0001,
    Player_Category	= 0x0002,
    Bounty_Category	= 0x0004,
    Stash_Category = 0x0008,
    Wall_Category = 0x0010,
    BountyRadar_Category = 0x0020,
    ObstacleAvoider_Category = 0x0040
};

enum CollisionMask {
    Default_Collision = 0xffff,
    Player_Collision = CollisionMask::Default_Collision,
    Bounty_Collision = (CollisionMask::Default_Collision ^ (CollisionCategory::Bounty_Category | CollisionCategory::Stash_Category | CollisionCategory::Wall_Category)),
    Stash_Collision	= CollisionMask::Default_Collision,
    Wall_Collision = (CollisionMask::Default_Collision ^ (CollisionCategory::Wall_Category)),
    BountyRadar_Collision = CollisionCategory::Bounty_Category,
    ObstacleAvoid_Collisions = CollisionCategory::Player_Category
};

enum GameState {
    NOT_INITIALIZED = 0,
    RESTARTED,
    RUNNING,
    GAMEOVER,
    TERMINATED,
    MAX_GAMESTATES
};

static constexpr const char* GameState2String[] {
                "NOT_INITIALIZED",
                "RESTARTED",
                "RUNNING",
                "GAMEOVER",
                "TERMINATED",
        };

struct GameContext {
    float FreezeTime;
    float PlayTime;

    int	WinnerId;

    int	NumPlayer;

    GameContext() : FreezeTime(FLOAT_SETTING(DEFAULT_FREEZE_TIME)), PlayTime(FLOAT_SETTING(DEFAULT_PLAY_TIME)), WinnerId(-1), NumPlayer(0) {}
};

struct PlayerAction {
    float move;
    float turn;
};

struct PlayerState {
    float playerPositionX;
    float playerPositionY;

    float playerRotation;

    float playerPocketLoad;

    float playerStashLoad;

    bool playerDead;

    float playerReward;
};
