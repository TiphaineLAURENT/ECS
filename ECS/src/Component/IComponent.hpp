/*
** EPITECH PROJECT, 2021
** ECS
** File description:
** IComponent
*/

#ifndef ECS_ICOMPONENT_HPP
# define ECS_ICOMPONENT_HPP

#include "../Platform.hpp"
#include "../Entity/IEntity.hpp"

namespace ecs
{

  using ComponentId = ObjectId;
  using ComponentTypeId = TypeId;

  static const ComponentId INVALID_COMPONENT_ID = INVALID_OBJECT_ID;

  template<class T>
  class Component;

  class IComponent
  {
    protected:
	  ComponentId _hashValue;
	  ComponentId _componentId;
	  EntityId    _owner;
	  bool        _enabled;

    public:
	  IComponent() = default;
	  virtual ~IComponent() = default;

    public:
	  inline const bool operator==(const IComponent &other) const
	  {
	  	return _hashValue == other._hashValue;
	  }

	  inline const bool operator!=(const IComponent &other) const
	  {
		  return _hashValue != other._hashValue;
	  }

    public:
	  inline void setComponentId(ComponentId componentId)
	  {
		  _componentId = componentId;
	  }

	  inline const ComponentId getComponentId() const
	  {
		  return _componentId;
	  }

	  inline void setHashValue(ComponentId hashValue)
	  {
		  _hashValue = hashValue;
	  }

	  inline void setOwner(EntityId owner)
	  {
		  _owner = owner;
	  }

	  inline const EntityId getOwner() const
	  {
	  	return _owner;
	  }

	  inline void setActive(bool state)
	  {
	  	_enabled = state;
	  }

	  inline bool isActive() const
	  {
	  	return _enabled;
	  }

  };

}

#endif //ECS_ICOMPONENT_HPP
