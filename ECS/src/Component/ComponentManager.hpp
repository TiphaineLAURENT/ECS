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
          [[nodiscard]] static ComponentManager &getInstance();
          template <typename C>
          static auto &getComponentContainer()
          {
                  static_assert(
                          std::is_base_of_v<IComponent, C>,
                          "Component must be derived from IComponent"
                          );

                  auto &instance = getInstance();

                  auto container = instance.getContainer<C>();
                  if (container == nullptr)
                  {
                          return *instance.createContainer<C>();
                  }
                  return *container;
          }

          template <typename C, typename Container = C, class ...ARGS>
          static C *addComponent(IEntity *entity, ARGS &&... args)
          {
                  if constexpr (std::is_same_v<C, Container>)
                  {
                          auto &container = getComponentContainer<C>();
                          return container.addComponent(
                                  entity,
                                  std::forward<ARGS>(args)...
                          );
                  }
                  else
                  {
                          auto &container = getComponentContainer<Container>();
                          return container.addComponent<C>(
                                  entity,
                                  std::forward<ARGS>(args)...
                          );
                  }
          }
          template <typename C, typename Container = C>
          [[nodiscard]] static C *getComponent(EntityID entityID)
          {
                  auto &container = getComponentContainer<Container>();

                  return container.getComponent(entityID);
          }
          template <typename C>
          [[nodiscard]] static ComponentView<C> getComponents(EntityID entityID)
          {
                  auto &container = getComponentContainer<C>();

                  return container.getComponents(entityID);
          }
          template <class C>
          [[noreturn]] static void removeComponent(EntityID entityID)
          {
                  auto &container = getComponentContainer<C>();

                  container.removeComponent(entityID);
          }

          template <class C>
          [[nodiscard]] static CComponentIterator<C> begin()
          {
                  return getComponentContainer<C>().begin();
          }
          template <class C>
          [[nodiscard]] static CComponentIterator<C> end()
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
                  auto pointer = container.get();
                  _containers[componentTypeID] = std::move(container);

                  return pointer;
          }

          template <class C>
          [[nodiscard]] ComponentContainer<C> *getContainer()
          {
                  const auto componentTypeID = C::_componentTypeID;
                  auto it = _containers.find(componentTypeID);
                  if (it != _containers.end()) {
                          return static_cast<ComponentContainer<C>*>(it->second.get());
                  }
                  return nullptr;
          }
  };

  std::ostream &operator<<(std::ostream &out, const ComponentManager &);

}

#endif /* !ECS_COMPONENTMANAGER_HPP */
