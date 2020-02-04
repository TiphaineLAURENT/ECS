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
                  ++_componentTypeCount;
          } else {
                  _componentID = _componentTypeCount++;
          }
  }

  IComponent::~IComponent()
  {
          _freeID.push_back(_componentID);
          --_componentTypeCount;
  }

  const size_t &IComponent::get_component_type_count()
  {
          return _componentTypeCount;
  }

  const ComponentID &IComponent::get_id() const
  {
          return _componentID;
  }

  const EntityID &IComponent::get_owner_id() const
  {
          return _owner->get_id();
  }

  IComponent &IComponent::enable()
  {
          _active = true;
          return *this;
  }

  IComponent &IComponent::disable()
  {
          _active = false;
          return *this;
  }

  bool IComponent::is_enabled() const
  {
          return _active;
  }

  IComponent &IComponent::set_owner(NonOwningPointer<IEntity> entity)
  {
          replace_pointer(_owner, entity);

          return *this;
  }
  NonOwningPointer<IEntity> IComponent::get_owner() const
  {
          return _owner;
  }

  std::ostream &operator<<(std::ostream &out, const NonOwningPointer<IComponent> component)
  {
          out << "{c "
              << "ID: " << component->get_id() << ", "
              << "Count: " << component->get_component_type_count() << ", "
              << "TypeID: " << component->get_component_type_id() << ", "
              << "TypeName: " << typeid(component).name() << ", "
              << "Owner: " << component->get_owner_id() << ", "
              << "Active: " << component->is_enabled() << true
              << " }";
          return out;
  }

}
