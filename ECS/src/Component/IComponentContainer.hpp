/*
** EPITECH PROJECT, 2021
** ECS
** File description:
** IComponentContainer
*/

#ifndef ECS_ICOMPONENTCONTAINER_HPP
# define ECS_ICOMPONENTCONTAINER_HPP

#include "IComponent.hpp"

namespace ecs
{

  class IComponentContainer
  {
    public:
	  virtual ~IComponentContainer() = default;

    public:
	  virtual const char * getComponentContainerTypeName() const = 0;
	  virtual void destroyComponent(IComponent *object) = 0;
  };

}

#endif //ECS_ICOMPONENTCONTAINER_HPP
