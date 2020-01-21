/*
** EPITECH PROJECT, 2021
** ECS
** File description:
** Component
*/

#ifndef ECS_COMPONENT_HPP
#define ECS_COMPONENT_HPP

# include "IComponent.hpp"

namespace ecs
{
# define COMPONENT(component) component : public ecs::Component<component>

  template <class C>
  class Component : public IComponent
  {
// ATTRIBUTES
  private:
          static inline ComponentID _componentTypeCount{0};

  public:
          static inline const ComponentTypeID _componentTypeID{util::FamilyTypeID<IComponent>::getTypeID<C>()};

// METHODS
  public:// CONSTRUCTORS
          Component()
                : IComponent()
          {
                  ++_componentTypeCount;
          }
          ~Component() override
          {
                  --_componentTypeCount;
          }
          Component(const Component &copy) = default;
          Component(Component &&) noexcept = default;

  public: //OPERATORS
          Component &operator=(const Component &other) = default;
          Component &operator=(Component &&) noexcept = default;

  public:
          [[noreturn]] void setup() override
          {
          }
          [[nodiscard]] static size_t getComponentTypeCount()
          {
                  return _componentTypeCount;
          }

          [[nodiscard]] ComponentTypeID getComponentTypeID() const override
          {
                  return _componentTypeID;
          }

  private:
  };

  template <class C>
  std::ostream &operator<<(std::ostream &out, const Component<C> &);

}

#endif /* !ECS_COMPONENT_HPP */
