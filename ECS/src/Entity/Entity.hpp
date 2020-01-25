/*
** EPITECH PROJECT, 2021
** ECS
** File description:
** Entity
*/

#ifndef ECS_ENTITY_HPP
# define ECS_ENTITY_HPP

# include <ostream>

# include "IEntity.hpp"

namespace ecs
{
# define ENTITY(entity) entity : public ecs::Entity<entity>

  template <class E>
  class Entity : public IEntity
  {
// ATTRIBUTES
  private:
  public:
          static inline const EntityTypeID _entityTypeID{util::FamilyTypeID<IEntity>::get_type_id<E>()};

// METHODS
  public:// CONSTRUCTORS
          Entity() = default;
          ~Entity() override = default;
          Entity(const Entity &copy) = default;
          Entity(Entity &&) noexcept = default;

  public: //OPERATORS
          Entity &operator=(const Entity &other) = default;
          Entity &operator=(Entity &&) noexcept = default;

  public:
          [[nodiscard]] EntityTypeID get_entity_type_id() const override
          {
                  return _entityTypeID;
          }

  private:
  };

  template <class E>
  std::ostream &operator<<(std::ostream &out, const Entity<E> &);

}

#endif /* !ECS_ENTITY_HPP */
