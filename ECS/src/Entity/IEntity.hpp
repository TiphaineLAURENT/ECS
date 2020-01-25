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
          [[nodiscard]] static EntityID get_entity_count();

          [[nodiscard]] const EntityID &get_id() const;
          [[nodiscard]] virtual EntityTypeID get_entity_type_id() const = 0;

          IEntity &enable();
          IEntity &disable();
          [[nodiscard]] bool is_enabled() const;

          template <class C, class Container = C, class ...ARGS>
          NonOwningPointer<C> create_component(ARGS &&... args)
          {
                  return ComponentManager::create_component<C, Container>(
                          this,
                          std::forward<ARGS>(args)...
                  );
          }
          template <class C, class Container = C>
          [[nodiscard]] NonOwningPointer<C> get_component() const
          {
                  return ComponentManager::get_component<C, Container>(_entityID);
          }
          template <class C>
          [[nodiscard]] ComponentView<C> get_components() const
          {
                  return ComponentManager::get_components<C>(_entityID);
          }
          template <class C>
          void erase_component()
          {
                  ComponentManager::erase_for_entity<C>(_entityID);
          }

  private:
  };

  std::ostream &operator<<(std::ostream &out, const NonOwningPointer<IEntity>);
}

#endif /* !ECS_IENTITY_HPP */
