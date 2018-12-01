/*
** EPITECH PROJECT, 2021
** ECS
** File description:
** ComponentContainer
*/

#ifndef ECS_COMPONENTCONTAINER_HPP
# define ECS_COMPONENTCONTAINER_HPP

# include <ostream>
# include <memory>
# include "IComponent.hpp"

namespace ecs
{

  template <class C>
  class ComponentContainer
  {
// ATTRIBUTES
    private:
	  std::vector<std::unique_ptr<IComponent>> _components;

    public:

// METHODS
    public:// CONSTRUCTORS
	  ComponentContainer();
	  ~ComponentContainer() = default;
	  ComponentContainer(const ComponentContainer &copy) = default;
	  ComponentContainer(ComponentContainer &&) noexcept = default;

    public: //OPERATORS
	  ComponentContainer &operator=(const ComponentContainer &other) = default;
	  ComponentContainer &operator=(ComponentContainer &&) = default;

    public:
    private:
  };

  template <class C>
  std::ostream &operator<<(std::ostream &out, const ComponentContainer<C> &);

}

#endif /* !ECS_COMPONENTCONTAINER_HPP */
