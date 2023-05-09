#include <numeric>
#include <string>

using SystemPriority = std::size_t;
using SystemTypeId = std::size_t;

static const SystemPriority LOW_SYSTEM_PRIORITY	= 100;
static const SystemPriority NORMAL_SYSTEM_PRIORITY = 200;
static const SystemPriority HIGH_SYSTEM_PRIORITY = 300;

class SystemBase {
public:
    virtual ~SystemBase();

    virtual void preUpdate(float deltaTime) = 0;
    virtual void update(float deltaTime) = 0;
    virtual void postUpdate(float deltaTime) = 0;

    virtual std::string getSystemTypeName() const = 0;
    virtual SystemTypeId getStaticSystemTypeId() const = 0;
protected:
    SystemBase(SystemPriority priority = NORMAL_SYSTEM_PRIORITY, float updateIntreval_ms = -1.0f);
private:
    SystemPriority m_priority;
    float m_timeSinceLastUpdate;
    float m_updateInterval;
    uint8_t m_enabled : 1;
    uint8_t m_needUpdate : 1;
    uint8_t m_reserved : 6;
};