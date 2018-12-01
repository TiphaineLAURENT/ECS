/*
** EPITECH PROJECT, 2021
** ECS
** File description:
** Entity
*/

#include "Entity.hpp"

namespace ecs
{

  template<class E>
  const EntityTypeID Entity<E>::getEntityTypeID() const
  {
	  return _entityTypeID;
  }

}
