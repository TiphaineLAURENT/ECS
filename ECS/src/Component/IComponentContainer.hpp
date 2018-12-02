/*
** EPITECH PROJECT, 2021
** ECS
** File description:
** IComponentContainer
*/

#ifndef ECS_ICOMPONENTCONTAINER_HPP
# define ECS_ICOMPONENTCONTAINER_HPP

# include <ostream>
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
	  IComponentContainer() = default;
	  virtual ~IComponentContainer() = default;
	  IComponentContainer(const IComponentContainer &copy) = default;
	  IComponentContainer(IComponentContainer &&) noexcept = default;

    public: //OPERATORS
	  IComponentContainer &operator=(const IComponentContainer &other) = default;
	  IComponentContainer &operator=(IComponentContainer &&) = default;

    public:
	  virtual const char *getComponentContainerTypeName() const = 0;

	  virtual void removeComponent(const EntityID entityID) = 0;

    private:
  };

  std::ostream &operator<<(std::ostream &out, const IComponentContainer &);

}

#endif /* !ECS_ICOMPONENTCONTAINER_HPP */
