#include "../../include/ecs/system_manager/system_manager.h"

namespace ecs {
    SystemManager::SystemManager() {
        // log init system manager here
    }

    SystemManager::~SystemManager() {
        //log here delete system manager
    }

    void SystemManager::Update(float deltaTime) {
        for (const auto system : m_SystemWorkOrder) {
            system->increaseUpdateTime(deltaTime);


            if (system->isEnabled() && system->isNeedUpdate()) {
                system->preUpdate(deltaTime);
            }

        }
        for (const auto system : m_SystemWorkOrder) {
            if (system->isEnabled() && system->isNeedUpdate()) {
                system->update(deltaTime);
            }
        }
        for (const auto system : m_SystemWorkOrder) {
            if (system->isEnabled() && system->isNeedUpdate()) {
                system->postUpdate(deltaTime);
            }
        }
    }

    void SystemManager::UpdateSystemWorkOrder() {
        /// use dependency matrix and system regustry(private members) to create work order
        /// first test maybe
    }


}
