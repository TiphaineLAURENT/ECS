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
# include <vector>
# include <list>
# include <algorithm>
# include <string>

# include "IComponentContainer.hpp"

namespace ecs
{

  template <class C>
  using ComponentStorage = std::vector<std::unique_ptr<C>>;

  template <class C>
  using CComponentIterator =
  typename ComponentStorage<C>::iterator;

  template <class C>
  using ComponentView = std::list<C*>;

  template <class C>
  class ComponentContainer : public IComponentContainer
  {
// ATTRIBUTES
  private:
          ComponentStorage<C> _components{};

  public:

// METHODS
  public:// CONSTRUCTORS
          ComponentContainer() = default;
          ~ComponentContainer() override = default;
          ComponentContainer(const ComponentContainer &copy) = delete;
          ComponentContainer(ComponentContainer &&) noexcept = delete;

  public: //OPERATORS
          ComponentContainer &operator=(const ComponentContainer &other) = delete;
          ComponentContainer &operator=(ComponentContainer &&) noexcept = delete;

  public:
          [[nodiscard]] const std::string &get_component_type_name() const override
          {
                  static const std::string componentTypeName{typeid(C).name()};

                  return componentTypeName;
          }

          template <class Custom = C, class ...ARGS>
          NonOwningPointer<Custom> create(NonOwningPointer<IEntity> entity, ARGS &&... args)
          {
                  static_assert(
                          std::is_base_of<IComponent, C>::value,
                          "Component must be derived from IComponent"
                  );

                  auto component = std::make_unique<Custom>(std::forward<ARGS>(args)...);
                  auto pointer = component.get();
                  component->set_owner(entity);
                  component->setup();

                  _components.push_back(std::move(component));
                  return pointer;
          }
          [[nodiscard]] NonOwningPointer<C> get_for_entity(EntityID entityID)
          {
                  auto iter = std::find_if(_components.begin(), _components.end(),
                                           [entityID] (const auto &component)
                                           {
                                                   return component->get_owner_id() == entityID;
                                           }
                  );
                  if (iter != _components.end())
                  {
                          return iter->get();
                  }
                  return nullptr;
          }
          [[nodiscard]] ComponentView<C> get_components(EntityID entityID)
          {
                  auto components = ComponentView<C>{};

                  for (auto &component : _components) {
                          if (component->get_owner_id() == entityID) {
                                  components.push_back(component.get());
                          }
                  }

                  return components;
          }
          [[nodiscard]] const ComponentView<C> get_components(EntityID entityID) const
          {
                  auto components = ComponentView<C>{};

                  for (auto &component : _components) {
                          if (component->get_owner_id() == entityID) {
                                  components.push_back(component.get());
                          }
                  }
                  return components;
          }
          void erase_for_entity(EntityID entityID) override
          {
                  auto toErase = std::remove_if(_components.begin(), _components.end(),
                                                [entityID] (const auto &component)
                                                {
                                                        return component->get_owner_id() == entityID;
                                                });
                  _components.erase(toErase);
          }
          void erase(ComponentID componentID) override
          {
                  auto toErase = std::remove_if(_components.begin(), _components.end(),
                                                [componentID] (const auto &component)
                                                {
                                                        return component->get_id() == componentID;
                                                });
                  _components.erase(toErase);
          }

          [[nodiscard]] CComponentIterator<C> begin()
          {
                  return _components.begin();
          }
          [[nodiscard]] CComponentIterator<C> end()
          {
                  return _components.end();
          }

          [[nodiscard]] ComponentStorage<C> &get_components()
          {
                  return _components;
          }

          [[nodiscard]] const ComponentStorage<C> &get_components() const
          {
                  return _components;
          }

  private:
  };

  template <class C>
  std::ostream &operator<<(std::ostream &out, const ComponentContainer<C> &);

}

#endif /* !ECS_COMPONENTCONTAINER_HPP */
