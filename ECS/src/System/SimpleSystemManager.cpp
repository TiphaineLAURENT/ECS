//
// Created by tiphaine on 06/04/19.
//

#include <cassert>

#include "SystemManager.hpp"
#include "SimpleSystemManager.hpp"

namespace ecs
{
        SimpleSystemManager &SimpleSystemManager::getInstance()
        {
                static SimpleSystemManager instance;
                return instance;
        }

  void SimpleSystemManager::update(Interval deltaTime)
  {
          SimpleSystemManager &instance = getInstance();

          for (auto &system : instance._systems) {
                  system.second->preUpdate(deltaTime);
          }

          for (auto &system : instance._systems) {
                  system.second->update(deltaTime);
          }

          for (auto &system : instance._systems) {
                  system.second->postUpdate(deltaTime);
          }
  }

}
