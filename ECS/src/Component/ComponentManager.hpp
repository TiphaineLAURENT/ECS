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
          [[nodiscard]] static ComponentManager &get_instance();
          template <class C>
          static auto &get_component_container()
          {
                  static_assert(
                          std::is_base_of_v<IComponent, C>,
                          "Component must be derived from IComponent"
                          );

                  auto &instance = get_instance();

                  auto container = instance.get_container<C>();
                  if (container == nullptr)
                  {
                          return *instance.create_container<C>();
                  }
                  return *container;
          }

          template <class C, class Container = C, class ...ARGS>
          static NonOwningPointer<C> create_component(NonOwningPointer<IEntity> entity, ARGS &&... args)
          {
                  if constexpr (std::is_same_v<C, Container>)
                  {
                          auto &container = get_component_container<C>();
                          return container.create(
                                  entity,
                                  std::forward<ARGS>(args)...
                          );
                  }
                  else
                  {
                          auto &container = get_component_container<Container>();
                          return container.template create<C>(
                                  entity,
                                  std::forward<ARGS>(args)...
                          );
                  }
          }
          template <class C, class Container = C>
          [[nodiscard]] static NonOwningPointer<C> get_component(EntityID entityID)
          {
                  auto &container = get_component_container<Container>();

                  return container.get_for_entity(entityID);
          }
          template <class C>
          [[nodiscard]] static ComponentView<C> get_components(EntityID entityID)
          {
                  auto &container = get_component_container<C>();

                  return container.get_components(entityID);
          }
          template <class C>
          static void erase_for_entity(EntityID entityID)
          {
                  auto &container = get_component_container<C>();

                  container.erase_for_entity(entityID);
          }

          template <class C>
          [[nodiscard]] static CComponentIterator<C> begin()
          {
                  return get_component_container<C>().begin();
          }
          template <class C>
          [[nodiscard]] static CComponentIterator<C> end()
          {
                  return get_component_container<C>().end();
          }

          [[nodiscard]] size_t get_container_count() const
          {
                  return _containers.size();
          }

  private:
          template <class C>
          NonOwningPointer<ComponentContainer<C>> create_container()
          {
                  const auto componentTypeID = C::_componentTypeID;
                  auto container = std::make_unique<ComponentContainer<C>>();
                  auto pointer = container.get();
                  _containers[componentTypeID] = std::move(container);

                  return pointer;
          }

          template <class C>
          [[nodiscard]] NonOwningPointer<ComponentContainer<C>> get_container()
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
