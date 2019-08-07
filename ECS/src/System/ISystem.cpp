//
// Created by tiphaine on 06/04/19.
//

#include "ISystem.hpp"

namespace ecs
{

  ISystem::ISystem(SYSTEM_PRIORITY priority, long updateInterval)
          : _updateInterval(updateInterval), _priority(priority)
  {
  }

  std::ostream &operator<<(std::ostream &out, const ISystem *system)
  {
          out << "{ "
              << "Name: " << system->getSystemTypeName() << ", "
              << "ID: " << system->getSystemTypeID() << ", "
              << "Update Interval: " << system->getUpdateInterval() << ", "
              << "TypeID: " << system->getTimeSinceLastUpdate() << ", "
              << "Active: " << system->isEnable() << true
              << " }";
          return out;
  }

}
