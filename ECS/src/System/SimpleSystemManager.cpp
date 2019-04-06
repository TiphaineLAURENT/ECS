//
// Created by tiphaine on 06/04/19.
//

#include <cassert>
#include "SystemManager.hpp"
#include "SimpleSystemManager.hpp"

namespace ecs
{
  SystemManager *SystemManager::_instance = nullptr;

  SystemManager &SystemManager::getInstance()
  {
          if (_instance == nullptr)
                  _instance = new SystemManager;
          return *_instance;
  }

  void SystemManager::update()
  {
          SystemManager &instance = getInstance();

          for (auto &system : instance._systems) {
                  system.second->preUpdate();
          }

          for (auto &system : instance._systems) {
                  system.second->update();
          }

          for (auto &system : instance._systems) {
                  system.second->postUpdate();
          }
  }

}
