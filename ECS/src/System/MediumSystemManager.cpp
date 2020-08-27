//
// Created by Tiphaine LAURENT on 06/08/2019.
//

#include "MediumSystemManager.hpp"

namespace ecs
{
        void MediumSystemManager::update(Interval deltaTime)
        {
                for (auto &system : m_orderedSystems)
                {
                        if (system->m_timeSinceLastUpdate += deltaTime;
                            system->m_timeSinceLastUpdate >= system->m_updateInterval)
                        {
                                system->update(deltaTime);
                                system->m_timeSinceLastUpdate = 0;
                        }
                }
        }

}    // namespace ecs
