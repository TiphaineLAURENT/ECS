/*
** EPITECH PROJECT, 2021
** ECS
** File description:
** ComponentManager
*/

#include "ComponentManager.hpp"

namespace ecs
{

  ComponentManager &ComponentManager::get_instance()
  {
          static ComponentManager instance;
          return instance;
  }

}
