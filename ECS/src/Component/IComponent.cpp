/*
** EPITECH PROJECT, 2021
** ECS
** File description:
** IComponent
*/

#include "IComponent.hpp"

namespace ecs
{

  IComponent::IComponent()
	  : _componentID(INVALID_COMPONENT_ID)
  {
	  if (!_freeID.empty()) {
		  _componentID = _freeID.back();
		  _freeID.pop_back();
	  } else {
		  _componentID = _componentCount++;
	  }
  }

  const ComponentID IComponent::getEntityCount()
  {
	  return _componentCount;
  }

  const ComponentID IComponent::getComponentID() const
  {
	  return _componentID;
  }

  IComponent::~IComponent()
  {
	  _freeID.push_back(_componentID);
  }

  const EntityID IComponent::getOwner() const
  {
	  return _owner;
  }

  IComponent &IComponent::setActive(bool state)
  {
	  _active = state;
	  return *this;
  }

  const bool IComponent::isActive() const
  {
	  return _active;
  }

  IComponent &IComponent::setOwner(const EntityID entityID)
  {
	  _owner = entityID;

	  return *this;
  }

}
