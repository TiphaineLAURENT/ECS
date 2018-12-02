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

  template<class C, class... ARGS>
  C &ComponentManager::addComponent(const EntityID entityID, ARGS&&... args)
  {
	  ComponentContainer<C> &container = getComponentContainer<C>();

	  return container.addComponent(std::forward(args)...);
  }

  template<class C>
  C &ComponentManager::getComponent(const EntityID entityID)
  {
	  ComponentContainer<C> &container = getComponentContainer<C>();

	  return container.getComponent(entityID);
  }

  template<class C>
  void ComponentManager::removeComponent(const EntityID entityID)
  {
	  ComponentContainer<C> &container = getComponentContainer<C>();

	  container.removeComponent(entityID);
  }

  template<class C>
  ComponentContainer<C> &ComponentManager::getComponentContainer()
  {
	  static_assert(std::is_base_of<IComponent, C>::value,
	                "Component must be derived from IComponent");

	  const ComponentTypeID componentTypeID = C::_componentTypeID;
	  return getInstance()._containers[componentTypeID];
  }
}
