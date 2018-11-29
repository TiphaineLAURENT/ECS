/*
** EPITECH PROJECT, 2021
** ECS
** File description:
** Entity
*/

#include "Entity.hpp"

namespace ecs
{

  size_t Entity::_maxId = 0;

  Entity::Entity()
	  : _id(_maxId++)
  {
  }

}
