/*
** EPITECH PROJECT, 2021
** ECS
** File description:
** ComponentManager
*/

#include "ComponentManager.hpp"

namespace ecs
{

  ComponentManager *ComponentManager::_instance = nullptr;

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
	  ComponentManager &instance = getInstance();

	  if (instance._containers.find(componentTypeID)
	      == instance._containers.end()) {
		  instance._containers.try_emplace(componentTypeID);
	  }

	  return instance._containers[componentTypeID];
  }

  template<class C>
  CComponentIterator<C> ComponentManager::begin()
  {
	  return getComponentContainer<C>().begin();
  }

  template<class C>
  CComponentIterator<C> ComponentManager::end()
  {
	  return getComponentContainer<C>().end();
  }
}
