/*
** EPITECH PROJECT, 2021
** ECS
** File description:
** Component
*/

#include "Component.hpp"

namespace ecs
{

  template<class C>
  const ComponentTypeID Component<C>::getComponentTypeID() const
  {
	  return _componentTypeID;
  }

}
