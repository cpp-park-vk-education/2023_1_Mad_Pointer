#pragma once
#include <numeric>
#include <string>
namespace ecs {
    template<class T>
    class System;

    using SystemPriority = std::size_t;
    using SystemTypeId = std::size_t;

    static const SystemPriority LOW_SYSTEM_PRIORITY	= 100;
    static const SystemPriority NORMAL_SYSTEM_PRIORITY = 200;
    static const SystemPriority HIGH_SYSTEM_PRIORITY = 300;

    class SystemBase {
    friend class SystemManager;
    public:
        virtual ~SystemBase();

        virtual void preUpdate(float deltaTime) = 0;
        virtual void update(float deltaTime) = 0;
        virtual void postUpdate(float deltaTime) = 0;

        virtual std::string getSystemTypeName() const = 0;
        virtual const SystemTypeId getStaticSystemTypeId() const = 0;

        void increaseUpdateTime(float deltaTime) {
            m_timeSinceLastUpdate += deltaTime;
        }

        bool isNeedUpdate() const {
            return m_needUpdate;
        }

        bool isEnabled() const {
            return m_enabled;
        }
    protected:
        SystemBase(SystemPriority priority = NORMAL_SYSTEM_PRIORITY, float updateInterval_ms = -1.0f);
    private:
        SystemPriority m_priority;
        float m_timeSinceLastUpdate;
        float m_updateInterval;
        bool m_enabled = true;
        bool m_needUpdate = true;
    };
}
