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
# include <map>
# include "IComponentContainer.hpp"

namespace ecs
{

  template <class C>
  using CComponentIterator =
  typename std::map<EntityID, std::unique_ptr<IComponent>>::iterator;

  template <class C>
  class ComponentContainer : public IComponentContainer
  {
// ATTRIBUTES
    private:
	  std::map<EntityID, std::unique_ptr<IComponent>> _components;

    public:

// METHODS
    public:// CONSTRUCTORS
	  ComponentContainer();
	  ~ComponentContainer() override = default;
	  ComponentContainer(const ComponentContainer &copy) = default;
	  ComponentContainer(ComponentContainer &&) noexcept = default;

    public: //OPERATORS
	  ComponentContainer &operator=(const ComponentContainer &other) = default;
	  ComponentContainer &operator=(ComponentContainer &&) noexcept = default;

    public:
	  const char *getComponentContainerTypeName() const override;

	  template <class ...ARGS>
	  C &addComponent(const EntityID entityID, ARGS&&... args);
	  C &getComponent(const EntityID entityID);
	  void removeComponent(const EntityID entityID) override;

	  CComponentIterator<C> begin();
	  CComponentIterator<C> end();

    private:
  };

  template <class C>
  std::ostream &operator<<(std::ostream &out, const ComponentContainer<C> &);

}

#endif /* !ECS_COMPONENTCONTAINER_HPP */
