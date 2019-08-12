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


namespace ecs
{

  using ComponentContainerMap = std::unordered_map<ComponentTypeID,
                                                   std::unique_ptr<IComponentContainer>>;

  class ComponentManager
  {
// ATTRIBUTES
  private:
          ComponentContainerMap _containers{};

  public:

// METHODS
  public:// CONSTRUCTORS
          constexpr ComponentManager() = default;
          ~ComponentManager() = default;
          ComponentManager(const ComponentManager &copy) = delete;
          ComponentManager(ComponentManager &&) noexcept = delete;

  public: //OPERATORS
          ComponentManager &operator=(const ComponentManager &other) = delete;
          ComponentManager &operator=(ComponentManager &&) = delete;

  public:
          static ComponentManager &getInstance();
          template <class C>
          constexpr static auto &getComponentContainer()
          {
                  static_assert(
                          std::is_base_of<IComponent, C>::value,
                          "Component must be derived from IComponent"
                  );

                  auto &instance = getInstance();

                  auto container = instance.getContainer<C>();
                  if (container == nullptr) {
                          return *instance.createContainer<C>();
                  }
                  return *container;
          }

          template <class C, class ...ARGS>
          static C *addComponent(IEntity *entity, ARGS &&... args)
          {
                  auto &container = getComponentContainer<C>();
                  return container.addComponent(
                          entity,
                          std::forward<ARGS>(args)...
                  );
          }
          template <class C>
          [[nodiscard]] static C *getComponent(EntityID entityID)
          {
                  auto &container = getComponentContainer<C>();

                  return container.getComponent(entityID);
          }
          template <class C>
          [[nodiscard]] static std::vector<C *> getComponents(EntityID entityID)
          {
                  auto &container = getComponentContainer<C>();

                  return container.getComponents(entityID);
          }
          template <class C>
          static void removeComponent(EntityID entityID)
          {
                  auto &container = getComponentContainer<C>();

                  container.removeComponent(entityID);
          }

          template <class C>
          static CComponentIterator<C> begin()
          {
                  return getComponentContainer<C>().begin();
          }
          template <class C>
          static CComponentIterator<C> end()
          {
                  return getComponentContainer<C>().end();
          }

          [[nodiscard]] size_t getContainerCount() const
          {
                  return _containers.size();
          }

  private:
          template <class C>
          ComponentContainer<C> *createContainer()
          {
                  const auto componentTypeID = C::_componentTypeID;
                  auto container = std::make_unique<ComponentContainer<C>>();
                  _containers[componentTypeID] = std::move(container);

                  return static_cast<ComponentContainer<C> *>(_containers[componentTypeID]
                          .get());
          }

          template <class C>
          [[nodiscard]] ComponentContainer<C> *getContainer()
          {
                  const auto componentTypeID = C::_componentTypeID;
                  auto it = _containers.find(componentTypeID);
                  if (it != _containers.end()) {
                          return static_cast<ComponentContainer<C> *>(it->second
                                                                        .get());
                  }
                  return nullptr;
          }
  };

  std::ostream &operator<<(std::ostream &out, const ComponentManager &);

}

#endif /* !ECS_COMPONENTMANAGER_HPP */
