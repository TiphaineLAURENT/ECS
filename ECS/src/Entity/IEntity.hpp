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

namespace ecs
{

  using EntityID = util::ID;
  static const EntityID        INVALID_ENTITY_ID = util::INVALID_ID;

  using EntityTypeID = util::ID;

  class IEntity
  {
// ATTRIBUTES
    private:
	  EntityID                     _entityID;
	  static std::vector<EntityID> _freeID;
	  static EntityID              _entityCount;
	  EntityTypeID _entityTypeID;

	  bool _active;

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
	  static const EntityID getEntityCount();

	  const EntityID getEntityID() const;
	  virtual const EntityTypeID getEntityTypeID() const = 0;

	  IEntity &setActive(bool state);
	  const bool isActive() const;

	  template <class C, class ...ARGS>
	  C &addComponent(ARGS&&... args);
	  template <class C>
	  C &getComponent();
	  template <class C>
	  IEntity &removeComponent();

    private:
  };

  std::ostream &operator<<(std::ostream &out, const IEntity &);
}

#endif /* !ECS_IENTITY_HPP */
