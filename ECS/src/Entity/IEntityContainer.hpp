/*
** EPITECH PROJECT, 2021
** ECS
** File description:
** IEntityContainer
*/

#ifndef ECS_IENTITYCONTAINER_HPP
# define ECS_IENTITYCONTAINER_HPP

# include <ostream>
# include <string>

# include "IEntity.hpp"

namespace ecs
{

  class IEntityContainer
  {
// ATTRIBUTES
  private:
  public:

// METHODS
  public:// CONSTRUCTORS
          IEntityContainer() = default;
          virtual ~IEntityContainer() = default;
          IEntityContainer(const IEntityContainer &copy) = delete;
          IEntityContainer(IEntityContainer &&) noexcept = delete;

  public: //OPERATORS
          IEntityContainer &operator=(const IEntityContainer &other) = delete;
          IEntityContainer &operator=(IEntityContainer &&) = delete;

  public:
          [[nodiscard]] virtual const std::string &get_entity_type_name() const = 0;

          virtual void erase(EntityID) = 0;

  private:
  };

  std::ostream &operator<<(std::ostream &out, const IEntityContainer &);

}

#endif /* !ECS_IENTITYCONTAINER_HPP */
