/*
** EPITECH PROJECT, 2021
** ECS
** File description:
** IEntity
*/

#include "IEntity.hpp"

namespace ecs
{

  std::vector<EntityID> IEntity::_freeID = std::vector<EntityID>();
  EntityID IEntity::_entityCount = 0;

  const EntityTypeID IEntity::getEntityTypeID() const
  {
	  return _entityTypeID;
  }

  IEntity::IEntity()
	  : _entityID(INVALID_ENTITY_ID),
	    _active(true)
  {
	  if (!_freeID.empty()) {
		  _entityID = _freeID.back();
		  _freeID.pop_back();
	  } else {
		  _entityID = _entityCount++;
	  }
  }

  const EntityID IEntity::getEntityID() const
  {
	  return _entityID;
  }

  IEntity &IEntity::setActive(bool state)
  {
	  _active = state;
	  return *this;
  }

  const bool IEntity::isActive() const
  {
	  return _active;
  }

  const EntityID IEntity::getEntityCount()
  {
	  return _entityCount;
  }

  IEntity::~IEntity()
  {
	  _freeID.push_back(_entityID);
  }

  template<class C, class... ARGS>
  C &IEntity::addComponent(ARGS&&... args)
  {
	  return ComponentManager::addComponent<C>(_entityID,
	                                        std::forward<ARGS>(args)...);
  }

  template<class C>
  C &IEntity::getComponent()
  {
	  return ComponentManager::getComponent<C>(_entityID);
  }

  template<class C>
  IEntity &IEntity::removeComponent()
  {
	  return ComponentManager::removeComponent<C>(_entityID);
  }

}
