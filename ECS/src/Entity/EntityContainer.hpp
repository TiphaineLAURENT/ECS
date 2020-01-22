/*
** EPITECH PROJECT, 2021
** ECS
** File description:
** EntityContainer
*/

#ifndef ECS_ENTITYCONTAINER_HPP
# define ECS_ENTITYCONTAINER_HPP

# include <ostream>
# include <map>
# include <memory>
# include <string>

# include "IEntityContainer.hpp"

namespace ecs
{

  template <class E>
  using EntityMap = std::map<EntityID, std::unique_ptr<E>>;

  template <class E>
  using EEntityIterator =
  typename EntityMap<E>::iterator;

  template <class E>
  class EntityContainer : public IEntityContainer
  {
// ATTRIBUTES
  private:
          EntityMap<E> _entities{};

  public:

// METHODS
  public:// CONSTRUCTORS
          EntityContainer() = default;
          ~EntityContainer() override = default;
          EntityContainer(const EntityContainer &copy) = delete;
          EntityContainer(EntityContainer &&) noexcept = delete;

  public: //OPERATORS
          EntityContainer &operator=(const EntityContainer &other) = delete;
          EntityContainer &operator=(EntityContainer &&) noexcept = delete;

  public:
          [[nodiscard]] const std::string &getEntityContainerTypeName() const override
          {
                  static const std::string entityTypeName{typeid(E).name()};

                  return entityTypeName;
          }

          template <class ...ARGS>
          E &createEntity(ARGS &&...args)
          {
                  static_assert(
                          std::is_base_of<IEntity, E>::value,
                          "Entity must be derived from IEntity"
                  );

                  auto entity = std::make_unique<E>(std::forward(args)...);
                  auto pointer = entity.get();
                  const auto entityID = entity->getEntityID();

                  _entities[entityID] = std::move(entity);
                  return *pointer;
          }
          [[nodiscard]] E &getEntityById(EntityID entityID)
          {
                  return *_entities[entityID].get();
          }
          [[nodiscard]] EntityMap<E> &getEntities()
          {
                  return _entities;
          }
          [[nodiscard]] const EntityMap<E> &getEntities() const
          {
                  return _entities;
          }
          [[noreturn]] void destroyEntity(EntityID entityId) override
          {
                  _entities.erase(entityId);
          }

          [[nodiscard]] EEntityIterator<E> begin()
          {
                  return _entities.begin();
          }
          [[nodiscard]] EEntityIterator<E> end()
          {
                  return _entities.end();
          }

  private:
  };

  template <class E>
  std::ostream &operator<<(std::ostream &out, const EntityContainer<E> &);

}

#endif /* !ECS_ENTITYCONTAINER_HPP */
