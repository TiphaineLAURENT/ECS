//
// Created by tiphaine on 06/04/19.
//

#include "SystemManager.hpp"
#include <cassert>

namespace ecs
{
        SystemManager &SystemManager::get_instance()
        {
                static SystemManager instance;
                return instance;
        }

        SystemWorkStateMaks SystemManager::getSystemWorkState()
        {
                SystemManager &instance = get_instance();

                SystemWorkStateMaks mask(instance.m_systemWorkOrder.size());
                for (size_t i = 0; i < instance.m_systemWorkOrder.size(); ++i)
                {
                        mask[i] = instance.m_systemWorkOrder[i]->is_enabled();
                }

                return mask;
        }

        void SystemManager::setSystemWorkState(SystemWorkStateMaks mask)
        {
                SystemManager &instance = get_instance();

                assert(mask.size() == instance.m_systemWorkOrder.size()
                       && "Provided"
                          " mask "
                          "does not"
                          " match "
                          "current "
                          "used one");

                for (size_t i = 0; i < instance.m_systemWorkOrder.size(); ++i)
                {
                        if (mask[i])
                        {
                                instance.m_systemWorkOrder[i]->enable();
                        }
                        else
                        {
                                instance.m_systemWorkOrder[i]->disable();
                        }
                }
        }

        void updateSystemWorkOrder() {}

        void update() {}

}    // namespace ecs
