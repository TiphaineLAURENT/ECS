//
// Created by tiphaine on 06/04/19.
//

#include <cassert>
#include "SystemManager.hpp"

namespace ecs
{
  SystemManager &SystemManager::get_instance()
  {
          static SystemManager instance;
          return instance;
  }

  SystemWorkStateMaks SystemManager::getSystemWorkState()
  {
          SystemManager &instance = get_instance();

          SystemWorkStateMaks mask(instance._systemWorkOrder.size());
          for (size_t i = 0; i < instance._systemWorkOrder.size(); ++i) {
                  mask[i] = instance._systemWorkOrder[i]->is_enabled();
          }

          return mask;
  }

  void SystemManager::setSystemWorkState(SystemWorkStateMaks mask)
  {
          SystemManager &instance = get_instance();

          assert(mask.size() == instance._systemWorkOrder.size() && "Provided"
                                                                    " mask "
                                                                    "does not"
                                                                    " match "
                                                                    "current "
                                                                    "used one");

          for (size_t i = 0; i < instance._systemWorkOrder.size(); ++i) {
                  if (mask[i]) {
                          instance._systemWorkOrder[i]->enable();
                  } else {
                          instance._systemWorkOrder[i]->disable();
                  }
          }
  }

  void updateSystemWorkOrder()
  {

  }

  void update()
  {

  }

}
