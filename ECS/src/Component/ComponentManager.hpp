/*
** EPITECH PROJECT, 2021
** ECS
** File description:
** ComponentManager
*/

#ifndef ECS_COMPONENTMANAGER_HPP
# define ECS_COMPONENTMANAGER_HPP

# include <ostream>
# include <unordered_map>
# include "ComponentContainer.hpp"
# include "../Entity/IEntity.hpp"

namespace ecs
{

  class ComponentManager
  {
// ATTRIBUTES
    private:
	  static ComponentManager *_instance;

	  std::unordered_map<ComponentTypeID,
		  std::unique_ptr<ComponentContainer>> _containers;

    public:

// METHODS
    public:// CONSTRUCTORS
	  ComponentManager() = default;
	  ~ComponentManager() = default;
	  ComponentManager(const ComponentManager &copy) = delete;
	  ComponentManager(ComponentManager &&) noexcept = delete;

    public: //OPERATORS
	  ComponentManager &operator=(const ComponentManager &other) = delete;
	  ComponentManager &operator=(ComponentManager &&) = delete;

    public:
	  static ComponentManager &getInstance();

	  template <class C, class ...ARGS>
	  static C &addComponent(const EntityID entityID, ARGS&&... args);
	  template <class C>
	  static C &getComponent(const EntityID entityID);
	  template <class C>
	  static void removeComponent(const EntityID entityID);

    private:
  };

  std::ostream &operator<<(std::ostream &out, const ComponentManager &);

}

#endif /* !ECS_COMPONENTMANAGER_HPP */
