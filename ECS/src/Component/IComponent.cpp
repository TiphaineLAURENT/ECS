/*
** EPITECH PROJECT, 2021
** ECS
** File description:
** IComponent
*/

#include "IComponent.hpp"

namespace ecs
{

  std::vector<ComponentID> IComponent::_freeID;
  ComponentID IComponent::_componentCount = 0;

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

  ComponentID IComponent::getComponentCount()
  {
          return _componentCount;
  }

  ComponentID IComponent::getComponentID() const
  {
          return _componentID;
  }

  EntityID IComponent::getOwner() const
  {
          return _owner;
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

  IComponent &IComponent::setOwner(const EntityID entityID)
  {
          _owner = entityID;

          return *this;
  }

  std::ostream &operator<<(std::ostream &out, const IComponent *component)
  {
          out << "{c "
              << "ID: " << component->getComponentID() << ", "
              << "Count: " << component->getComponentCount() << ", "
              << "TypeID: " << component->getComponentTypeID() << ", "
              << "TypeName: " << typeid(component).name() << ", "
              << "Owner: " << component->getOwner() << ", "
              << "Active: " << component->isActive() << true
              << " }";
          return out;
  }

}
