//
// Created by tiphaine on 06/04/19.
//

#include "ISystem.hpp"

namespace ecs
{

  ISystem::ISystem(SYSTEM_PRIORITY priority, Interval updateInterval)
          : _updateInterval(updateInterval), _priority(priority)
  {
  }

  std::ostream &operator<<(std::ostream &out, const ISystem *system)
  {
          out << "{ "
              << "Name: " << system->get_system_type_name() << ", "
              << "ID: " << system->get_system_type_id() << ", "
              << "Update Interval: " << system->get_update_interval() << ", "
              << "TypeID: " << system->get_time_since_last_update() << ", "
              << "Active: " << system->is_enabled() << true
              << " }";
          return out;
  }

}
