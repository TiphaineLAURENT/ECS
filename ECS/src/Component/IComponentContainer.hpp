/*
** EPITECH PROJECT, 2021
** ECS
** File description:
** IComponentContainer
*/

#ifndef ECS_ICOMPONENTCONTAINER_HPP
# define ECS_ICOMPONENTCONTAINER_HPP

# include <ostream>
# include <string_view>

# include "IComponent.hpp"

namespace ecs
{

  class IComponentContainer
  {
// ATTRIBUTES
  private:
  public:

// METHODS
  public:// CONSTRUCTORS
          explicit IComponentContainer() = default;
          virtual ~IComponentContainer() = default;
          IComponentContainer(const IComponentContainer &copy) = delete;
          IComponentContainer(IComponentContainer &&) noexcept = delete;

  public: //OPERATORS
          IComponentContainer &operator=(const IComponentContainer &other) = delete;
          IComponentContainer &operator=(IComponentContainer &&) = delete;

  public:
          [[nodiscard]] virtual const std::string_view &get_component_type_name() const = 0;

          virtual void erase_for_entity(EntityID entityID) = 0;
          virtual void erase(ComponentID componentID) = 0;

          virtual size_t size() = 0;

  private:
  };

  std::ostream &operator<<(std::ostream &out, const IComponentContainer &);

}

#endif /* !ECS_ICOMPONENTCONTAINER_HPP */
