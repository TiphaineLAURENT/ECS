/*
** EPITECH PROJECT, 2021
** ECS
** File description:
** IComponent
*/

#ifndef ECS_ICOMPONENT_HPP
# define ECS_ICOMPONENT_HPP

# include <ostream>
# include <vector>

# include "../util/util.hpp"

namespace ecs
{
  class IEntity;

  using ComponentID = util::ID;
  using ComponentTypeID = util::ID;

  class IComponent
  {
// ATTRIBUTES
  private:
          static inline const ComponentID INVALID_COMPONENT_ID{util::INVALID_ID};

          ComponentID _componentID{INVALID_COMPONENT_ID};

          static inline ::std::vector<ComponentID> _freeID{};

          static inline size_t _componentTypeCount{0};

          NonOwningPointer<IEntity> _owner{nullptr};

          bool _active{true};

  public:

// METHODS
  public:// CONSTRUCTORS
          IComponent();
          virtual ~IComponent();
          IComponent(const IComponent &copy) = default;
          IComponent(IComponent &&) noexcept = default;

  public: //OPERATORS
          IComponent &operator=(const IComponent &other) = default;
          IComponent &operator=(IComponent &&) = default;

  public:
          virtual void setup() = 0;

          [[nodiscard]] static const size_t &get_component_type_count();

          [[nodiscard]] const ComponentID &get_id() const;
          [[nodiscard]] virtual ComponentTypeID get_component_type_id() const = 0;

          IComponent &set_owner(NonOwningPointer<IEntity> entity);
          [[nodiscard]] NonOwningPointer<IEntity> get_owner() const;
          [[nodiscard]] const EntityID &get_owner_id() const;

          IComponent &enable();
          IComponent &disable();
          [[nodiscard]] bool is_enabled() const;

  private:
  };

  ::std::ostream &operator<<(::std::ostream &out, const NonOwningPointer<IComponent>);

}

#endif /* !ECS_ICOMPONENT_HPP */
