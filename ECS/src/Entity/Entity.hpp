/*
** EPITECH PROJECT, 2021
** ECS
** File description:
** Entity
*/

#ifndef ECS_ENTITY_HPP
# define ECS_ENTITY_HPP

# include <ostream>
# include <memory>

namespace ecs
{

  class Entity
  {
// ATTRIBUTES
    private:
	  static size_t _maxId;
	  size_t _id;
	  std::unique_ptr<ComponentManager> _componentManager;

    public:

// METHODS
    public:// CONSTRUCTORS
	  Entity();
	  ~Entity() = default;
	  Entity(const Entity &copy) = default;
	  Entity(Entity &&) noexcept = default;

    public: //OPERATORS
	  Entity &operator=(const Entity &other) = default;
	  Entity &operator=(Entity &&) = default;

    public:
    private:
  };

  std::ostream &operator<<(std::ostream &out, const Entity &);

}

#endif /* !ECS_ENTITY_HPP */
