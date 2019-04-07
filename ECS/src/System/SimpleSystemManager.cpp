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
          if (_instance == nullptr)
                  _instance = new SimpleSystemManager;
          return *_instance;
  }

  /*void SimpleSystemManager::updateSystemOrder()
  {
          std::sort(_systems.begin(), _systems.end(),
                  [](std::pair<util::ID, std::unique_ptr<ISystem>> sys1,
                     std::pair<util::ID, std::unique_ptr<ISystem>> sys2) {
                          return static_cast<int>(sys1.second->getPriority())
                                 > static_cast<int>(sys1.second->getPriority());
                  });
  }*/

  void SimpleSystemManager::update()
  {
          SimpleSystemManager &instance = getInstance();

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
