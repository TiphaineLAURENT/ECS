/*
** EPITECH PROJECT, 2021
** ECS
** File description:
** IComponent
*/

#include "IComponent.hpp"
#include "IEntity.hpp"

namespace ecs
{

  IComponent::IComponent()
  {
          if (!_freeID.empty()) {
                  _componentID = _freeID.back();
                  _freeID.pop_back();
                  ++_componentCount;
          } else {
                  _componentID = _componentCount++;
          }
  }

  IComponent::~IComponent()
  {
          _freeID.push_back(_componentID);
          --_componentCount;
  }

  size_t IComponent::getComponentCount()
  {
          return _componentCount;
  }

  ComponentID IComponent::getComponentID() const
  {
          return _componentID;
  }

  EntityID IComponent::getOwnerId() const
  {
          return _ownerId;
  }

  IComponent &IComponent::setActive(bool state)
  {
          _active = state;
          return *this;
  }

  bool IComponent::isActive() const
  {
          return _active;
  }

  IComponent &IComponent::setOwner(NonOwningPointer<IEntity> entity)
  {
          const_cast<IEntity*>(_owner) = entity;
          _ownerId = _owner->getEntityID();

          return *this;
  }
  NonOwningPointer<IEntity> IComponent::getOwner() const
  {
          return _owner;
  }

  std::ostream &operator<<(std::ostream &out, const NonOwningPointer<IComponent> component)
  {
          out << "{c "
              << "ID: " << component->getComponentID() << ", "
              << "Count: " << component->getComponentCount() << ", "
              << "TypeID: " << component->getComponentTypeID() << ", "
              << "TypeName: " << typeid(component).name() << ", "
              << "Owner: " << component->getOwnerId() << ", "
              << "Active: " << component->isActive() << true
              << " }";
          return out;
  }

}
