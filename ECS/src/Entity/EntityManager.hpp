/*
** EPITECH PROJECT, 2021
** ECS
** File description:
** EntityManager
*/

#ifndef ECS_ENTITYMANAGER_HPP
# define ECS_ENTITYMANAGER_HPP

# include <ostream>
# include "EntityContainer.hpp"

namespace ecs
{

  using EntityContainerMap = std::unordered_map<EntityTypeID,
                                                std::unique_ptr<IEntityContainer>>;

  class EntityManager
  {
// ATTRIBUTES
  private:
          EntityContainerMap _containers{};

  public:

// METHODS
  public:// CONSTRUCTORS
          constexpr EntityManager() = default;
          ~EntityManager() = default;
          EntityManager(const EntityManager &copy) = delete;
          EntityManager(EntityManager &&) noexcept = delete;

  public: //OPERATORS
          EntityManager &operator=(const EntityManager &other) = delete;
          EntityManager &operator=(EntityManager &&) = delete;

  public:
          [[nodiscard]] static EntityManager &get_instance();
          template <class E>
          [[nodiscard]] constexpr static EntityContainer<E> &get_entity_container()
          {
                  static_assert(
                          std::is_base_of<IEntity, E>::value,
                          "Entity must be derived from IEntity"
                  );

                  const ComponentTypeID entityTypeID = E::_entityTypeID;
                  EntityManager &instance = get_instance();

                  if (instance._containers.find(entityTypeID)
                      == instance._containers.end()) {
                          auto container =
                                  std::make_unique<EntityContainer<E>>();
                          instance._containers[entityTypeID] = std::move(
                                  container
                          );
                  }

                  return *static_cast<EntityContainer<E> *>(instance
                          ._containers[entityTypeID].get());
          }

          template <class E, class ...ARGS>
          static E &create(ARGS &&... args)
          {
                  EntityContainer<E> &container = get_entity_container<E>();

                  return container.create(std::forward(args)...);
          }
          template <class E>
          [[nodiscard]] static E &get_entity(EntityID entityID)
          {
                  EntityContainer<E> &container = get_entity_container<E>();

                  return container.get_entity(entityID);
          }
          template <class E>
          static void remove_entity(EntityID entityID)
          {
                  EntityContainer<E> &container = get_entity_container<E>();

                  container.erase(entityID);
          }

          template <class E>
          [[nodiscard]] static CComponentIterator<E> begin();
          template <class E>
          [[nodiscard]] static CComponentIterator<E> end();

  private:
  };

  std::ostream &operator<<(std::ostream &out, const EntityManager &);

}

#endif /* !ECS_ENTITYMANAGER_HPP */
