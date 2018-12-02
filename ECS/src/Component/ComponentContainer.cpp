/*
** EPITECH PROJECT, 2021
** ECS
** File description:
** ComponentContainer
*/

#include "ComponentContainer.hpp"

namespace ecs
{

  template <class C>
  ComponentContainer<C>::ComponentContainer()
	  : _components()
  {
  }

  template <class C>
  const char *ComponentContainer<C>::getComponentContainerTypeName() const
  {
	  static const char *componentTypeName{typeid(C).name()};

	  return componentTypeName;
  }

  template <class C>
  template <class... ARGS>
  C &ComponentContainer<C>::addComponent(const EntityID entityID,
                                         ARGS&&... args
  )
  {
	  static_assert(std::is_base_of<IComponent, C>::value,
	                "Component must be derived from IComponent");

	  auto component = std::make_unique<C>(std::forward(args)...);
	  auto *iComponent = static_cast<IComponent*>(component.get());
	  iComponent->setOwner(entityID);

	  _components[iComponent->getOwner()] = component;
	  return *_components[entityID];
  }

  template <class C>
  C &ComponentContainer<C>::getComponent(const EntityID entityID)
  {
	  return _components[entityID];
  }

  template <class C>
  void ComponentContainer<C>::removeComponent(const EntityID entityID)
  {
	  _components.erase(entityID);
  }

  template <class C>
  CComponentIterator<C> ComponentContainer<C>::begin()
  {
	  return _components.begin();
  }

  template <class C>
  CComponentIterator<C> ComponentContainer<C>::end()
  {
	  return _components.end();
  }

}
