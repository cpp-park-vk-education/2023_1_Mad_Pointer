#pragma once
#include "../system/system_base.h"
#include <vector>
#include <memory>
#include <list>
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
        T* AddSystem(ARGS&&... systemArgs) {
            const auto systemTypeId = T::STATIC_SYSTEM_TYPE_ID;

            auto it = m_Systems.find(systemTypeId);
            if (it != m_Systems.end() && it->second != nullptr) {
                return (T*)it->second;
            }

            std::shared_ptr<T> system = std::make_shared(std::forward<ARGS>(systemArgs)...);
            system->m_systemManagerInstance = this;

            m_Systems[systemTypeId] = system;

            if (systemTypeId + 1 > m_SystemDependencyMatrix.size()) {
                m_SystemDependencyMatrix.resize(systemTypeId + 1);
                for (int i = 0; i < m_SystemDependencyMatrix.size(); ++i) {
                    m_SystemDependencyMatrix[i].resize(systemTypeId + 1);
                }
            }

            m_SystemWorkOrder.push_back(system);
            return system;
        }

        template<class System_, class Dependency_>
        void AddSystemDependency(System_ target, Dependency_ dependency) {
            const auto targetID = target->getStaticSystemId();
            const auto dependencyID = dependency->getStaticSystemId();

            m_SystemDependencyMatrix[targetID][dependencyID] = true;
        }

        template<class Target, class Dependency_, class... Dependencies>
        void AddSystemDependency(Target target, Dependency_ dependency, Dependencies&&... dependencies) {
            const auto targetID = target->getStaticSystemId();
            const auto dependencyID = dependency->getStaticSystemId();

            m_SystemDependencyMatrix[targetID][dependencyID] = true;

            AddSystemDependency(target, std::forward<Dependencies>(dependencies)...);
        }

        void UpdateSystemWorkOrder();

        template<class T>
        inline T* GetSystem() const {
            try {
                return (T*)m_Systems.at(T::STATIC_SYSTEM_TYPE_ID);
            } catch (std::exception& e) {
                return nullptr;
            }
        }

        template<class T>
        void EnableSystem() {
            if (GetSystem<T>()) {
                GetSystem<T>()->second->m_Enabled = true;
            }
        }

        template<class T>
        void DisableSystem() {
            if (GetSystem<T>()) {
                GetSystem<T>()->second->m_Enabled = false;
            }
        }

        template<class T>
        void SetSystemUpdateInterval(float intervalMs) {
            if (GetSystem<T>()) {
                GetSystem<T>()->second->m_updateInterval = intervalMs;
            }
        }

        template<class T>
        void SetSystemPriority(SystemPriority newPriority) {
            if (GetSystem<T>()) {
                GetSystem<T>()->second->m_priority = newPriority;
            }
        }

        SystemWorkStateMask GetSystemWorkState() const;

        void SetSystemWorkState(SystemWorkStateMask mask);

        template<class... ActiveSystems>
        SystemWorkStateMask GenerateActiveSystemWorkState(ActiveSystems&&... activeSystems) {
            SystemWorkStateMask mask(m_SystemWorkOrder.size(), false);
            std::vector<SystemBase*> enabledSystems = {activeSystems...};
            for (const auto system : enabledSystems) {
                for (int i = 0; i < m_SystemWorkOrder.size(); ++i) {
                    if (system->getStaticSystemTypeId() == m_SystemWorkOrder[i]->getStaticSystemTypeId()) {
                        mask[i] = true;
                    }
                }
            }
            return mask;
        }
    private:
        SystemRegistry m_Systems;
        SystemDependencyMatrix m_SystemDependencyMatrix;
        SystemWorkOrder m_SystemWorkOrder;
};

} // namespace ECS