/*
** EPITECH PROJECT, 2021
** ECS
** File description:
** IEntity
*/

#ifndef ECS_IENTITY_HPP
# define ECS_IENTITY_HPP

# include <ostream>
# include <vector>

# include "../util/util.hpp"
# include "../Component/ComponentManager.hpp"

namespace ecs
{

  using EntityID = util::ID;
  static const EntityID INVALID_ENTITY_ID = util::INVALID_ID;

  using EntityTypeID = util::ID;

  class IEntity
  {
// ATTRIBUTES
  private:
          EntityID _entityID{util::INVALID_ID};

          static inline std::vector<EntityID> _freeID{};

          static inline size_t _entityCount{0};

          EntityTypeID _entityTypeID{util::INVALID_ID};

          bool _active{true};

  public:

// METHODS
  public:// CONSTRUCTORS
          IEntity();
          virtual ~IEntity();
          IEntity(const IEntity &copy) = default;
          IEntity(IEntity &&) noexcept = default;

  public: //OPERATORS
          IEntity &operator=(const IEntity &other) = default;
          IEntity &operator=(IEntity &&) noexcept = default;

  public:
          [[nodiscard]] static EntityID getEntityCount();

          [[nodiscard]] EntityID getEntityID() const;
          [[nodiscard]] virtual EntityTypeID getEntityTypeID() const = 0;

          IEntity &setActive(bool state);
          [[nodiscard]] bool isActive() const;

          template <class C, class ...ARGS>
          C *addComponent(ARGS &&... args)
          {
                  return ComponentManager::addComponent<C>(
                          this,
                          std::forward<ARGS>(args)...
                  );
          }
          template <class C>
          [[nodiscard]] C *getComponent() const
          {
                  return ComponentManager::getComponent<C>(_entityID);
          }
          template <class C>
          [[nodiscard]] std::vector<C *const> getComponents() const
          {
                  return ComponentManager::getComponents<C>(_entityID);
          }
          template <class C>
          void removeComponent()
          {
                  ComponentManager::removeComponent<C>(_entityID);
          }

  private:
  };

  std::ostream &operator<<(std::ostream &out, const IEntity *);
}

#endif /* !ECS_IENTITY_HPP */
