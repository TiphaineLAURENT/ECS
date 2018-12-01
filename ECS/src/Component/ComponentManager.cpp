/*
** EPITECH PROJECT, 2021
** ECS
** File description:
** ComponentManager
*/

#include "ComponentManager.hpp"

namespace ecs
{

  ComponentManager &ComponentManager::getInstance()
  {
	  if (!_instance)
	  	_instance = new ComponentManager;

	  return *_instance;
  }
}
