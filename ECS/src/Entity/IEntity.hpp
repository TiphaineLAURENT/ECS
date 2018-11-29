/*
** EPITECH PROJECT, 2021
** ECS
** File description:
** IEntity
*/

#ifndef ECS_IENTITY_HPP
# define ECS_IENTITY_HPP

#include <utility>
#include "../Platform.hpp"
#include "../Component/ComponentManager.hpp"

namespace ecs
{

  using EntityTypeId = TypeId;
  using EntityId = Handle64;

  static const EntityId INVALID_ENTITY_ID = Handle64::INVALID_HANDLE;

  class IEntity
  {
    private:
	  ComponentManager *_componentManagerInstance;

    protected:
	  EntityId _entityId;
	  bool     _active;

    public:
	  IEntity() = default;
	  virtual ~IEntity() = default;

    public:
	  inline bool operator==(const IEntity &rhs) const
	  {
		  return _entityId == rhs._entityId;
	  }

	  inline bool operator!=(const IEntity &rhs) const
	  {
		  return _entityId != rhs._entityId;
	  }

	  inline bool operator==(const IEntity *rhs) const
	  {
		  return _entityId == rhs->_entityId;
	  }

	  inline bool operator!=(const IEntity *rhs) const
	  {
		  return _entityId != rhs->_entityId;
	  }

    public:
	  template<class T>
	  T *getComponent() const
	  {
		  return _componentManagerInstance->getComponent<T>(_entityId);
	  }

	  template<class T, class ...P>
	  T *addCommponent(P &&... param)
	  {
		  return _componentManagerInstance->addComponent<T>(_entityId,
		                                                    std::forward<P>(
			                                                    param
		                                                    )...
		  );
	  }

	  template<class T>
	  void removeComponent()
	  {
		  _componentManagerInstance->removeComponent<T>(_entityId);
	  }

	  virtual const EntityTypeId getStaticEntityTypeId() const = 0;

	  inline const EntityId getEntityId() const
	  {
	  	return _entityId;
	  }

	  void setActive(bool active)
	  {
	  	_active = active;
	  }

	  inline bool isActive() const
	  {
	  	return _active;
	  }

	  virtual void onEnable()
	  {}

	  virtual void onDisable()
	  {}
  };

}

#endif //ECS_IENTITY_HPP
