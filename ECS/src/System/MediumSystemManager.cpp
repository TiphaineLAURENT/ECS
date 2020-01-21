//
// Created by Tiphaine LAURENT on 06/08/2019.
//

#include "MediumSystemManager.hpp"


namespace ecs
{

  void MediumSystemManager::update(Interval deltaTime)
  {
          for (auto &system : _orderedSystems)
          {
                  system->_timeSinceLastUpdate += deltaTime;
                  if (system->_timeSinceLastUpdate >= system->_updateInterval)
                  {
                          system->update(deltaTime);
                          system->_timeSinceLastUpdate = 0;
                  }
          }
  }

}
