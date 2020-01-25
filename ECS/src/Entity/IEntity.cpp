/*
** EPITECH PROJECT, 2021
** ECS
** File description:
** IEntity
*/

#include "IEntity.hpp"
#include "../Component/ComponentManager.hpp"

namespace ecs
{

  EntityTypeID IEntity::get_entity_type_id() const
  {
          return _entityTypeID;
  }

  IEntity::IEntity()
  {
          if (!_freeID.empty()) {
                  _entityID = _freeID.back();
                  _freeID.pop_back();
                  _entityCount++;
          } else {
                  _entityID = _entityCount++;
          }
  }

  const EntityID &IEntity::get_id() const
  {
          return _entityID;
  }

  IEntity &IEntity::enable()
  {
          _active = true;
          return *this;
  }

  IEntity &IEntity::disable()
  {
          _active = false;
          return *this;
  }

  bool IEntity::is_enabled() const
  {
          return _active;
  }

  size_t IEntity::get_entity_count()
  {
          return _entityCount;
  }

  IEntity::~IEntity()
  {
          _freeID.push_back(_entityID);
  }

  std::ostream &operator<<(std::ostream &out, const IEntity *entity)
  {
          out << "{e "
              << "ID: " << entity->get_id() << ", "
              << "Entity count: " << entity->get_entity_count() << ", "
              << "Entity type ID: " << entity->get_entity_type_id() << ", "
              << "Entity type name: " << typeid(entity).name()
              << " }";

          return out;
  }

}
