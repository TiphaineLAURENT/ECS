//
// Created by tiphaine on 06/04/19.
//

#include <cassert>

#include "SimpleSystemManager.hpp"
#include "SystemManager.hpp"

namespace ecs
{
        SimpleSystemManager &SimpleSystemManager::get_instance()
        {
                static SimpleSystemManager instance;
                return instance;
        }

        void SimpleSystemManager::update(Interval deltaTime)
        {
                SimpleSystemManager &instance = get_instance();

                for (auto &system : instance.m_systems)
                {
                        system.second->pre_update(deltaTime);
                }

                for (auto &system : instance.m_systems)
                {
                        system.second->update(deltaTime);
                }

                for (auto &system : instance.m_systems)
                {
                        system.second->post_update(deltaTime);
                }
        }

}    // namespace ecs
