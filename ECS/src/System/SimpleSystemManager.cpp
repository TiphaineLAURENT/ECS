//
// Created by tiphaine on 06/04/19.
//

#include <cassert>

#include "SystemManager.hpp"
#include "SimpleSystemManager.hpp"

namespace ecs
{
  SimpleSystemManager *SimpleSystemManager::_instance = nullptr;

  SimpleSystemManager &SimpleSystemManager::getInstance()
  {
          if (_instance == nullptr) {
                  _instance = new SimpleSystemManager;
          }
          return *_instance;
  }

  void SimpleSystemManager::update(float deltaTime)
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
