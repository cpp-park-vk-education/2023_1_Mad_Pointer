#include "../system/system_base.h"
#include <vector>
#include <unordered_map>

namespace ecs {
    using SystemWorkStateMask = std::vector<bool>;

    class SystemManager {
    public:
        using SystemDependencyMatrix = std::vector<std::vector<bool>>;
        using SystemRegistry = std::unordered_map<uint64_t, SystemBase*>;
        using SystemWorkOrder = std::vector<SystemBase*>;

        SystemManager(const SystemManager&) = delete;
        SystemManager& operator=(SystemManager&) = delete;

        void Update(float deltaTime);

        SystemManager();
        ~SystemManager();

        template<class T, class... ARGS>
        T* AddSystem(ARGS&&... systemArgs) { }

        template<class System_, class Dependency_>
        void AddSystemDependency(System_ target, Dependency_ dependency){}

        template<class Target, class Dependency_, class... Dependencies>
        void AddSystemDependency(Target target, Dependency_ dependency, Dependencies&&... dependencies) {}

        void UpdateSystemWorkOrder();

        template<class T>
        inline T* GetSystem() const {}

        template<class T>
        void EnableSystem() {}

        template<class T>
        void DisableSystem() {}

        template<class T>
        void SetSystemUpdateInterval(float intervalMs) {}

        template<class T>
        void SetSystemPriority(SystemPriority newPriority) {}

        SystemWorkStateMask GetSystemWorkState() const;

        void SetSystemWorkState(SystemWorkStateMask mask);

        template<class... ActiveSystems>
        SystemWorkStateMask GenerateActiveSystemWorkState(ActiveSystems&&... activeSystems) {}
    private:
        SystemRegistry			m_Systems;
        SystemDependencyMatrix	m_SystemDependencyMatrix;
        SystemWorkOrder			m_SystemWorkOrder;
};

} // namespace ECS