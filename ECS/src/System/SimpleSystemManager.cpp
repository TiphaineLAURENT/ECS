//
// Created by tiphaine on 06/04/19.
//

#include <cassert>

#include "SystemManager.hpp"
#include "SimpleSystemManager.hpp"

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

          for (auto &system : instance._systems) {
                  system.second->pre_update(deltaTime);
          }

          for (auto &system : instance._systems) {
                  system.second->update(deltaTime);
          }

          for (auto &system : instance._systems) {
                  system.second->post_update(deltaTime);
          }
  }

}
