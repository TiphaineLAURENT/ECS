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

  template <typename C>
  using ComponentView = std::vector<C*>;

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
          [[nodiscard]] const std::string &getComponentContainerTypeName() const override
          {
                  static const std::string componentTypeName{typeid(C).name()};

                  return componentTypeName;
          }

          template <typename Custom = C, class ...ARGS>
          Custom *addComponent(IEntity *entity, ARGS &&... args)
          {
                  static_assert(
                          std::is_base_of<IComponent, C>::value,
                          "Component must be derived from IComponent"
                  );

                  auto component = std::make_unique<Custom>(std::forward<ARGS>(args)...);
                  component->setOwner(entity);
                  component->setup();

                  _components.push_back(std::move(component));
                  if constexpr (std::is_same_v<Custom, C>)
                  {
                          return _components.back().get();
                  }
                  else
                  {
                          return static_cast<Custom*>(_components.back().get());
                  }
          }
          [[nodiscard]] C *getComponent(EntityID entityID)
          {
                  auto iter = std::find_if(_components.begin(), _components.end(),
                                           [entityID] (const auto &component)
                                           {
                                                   return component->getOwnerId() == entityID;
                                           }
                  );
                  if (iter != _components.end())
                  {
                          return iter->get();
                  }
                  return nullptr;
          }
          [[nodiscard]] ComponentView<C> getComponents(EntityID entityID)
          {
                  auto components = ComponentView<C>{};

                  for (auto &component : _components) {
                          if (component->getOwnerId() == entityID) {
                                  components.emplace_back(component.get());
                          }
                  }
                  return components;
          }
          [[nodiscard]] const ComponentView<C> getComponents(EntityID entityID)
          const
          {
                  auto components = ComponentView{};

                  for (auto &component : _components) {
                          if (component->getOwnerId() == entityID) {
                                  components.emplace_back(component.get());
                          }
                  }
                  return components;
          }
          [[noreturn]] void removeComponent(EntityID entityID) override
          {
                  auto toErase = std::remove_if(_components.begin(), _components.end(),
                                                [entityID] (const auto &component)
                                                {
                                                        return component->getOwnerId() == entityID;
                                                });
                  _components.erase(toErase);
          }
          [[noreturn]] void removeComponentByID(ComponentID componentID)
          {
                  auto toErase = std::remove_if(_components.begin(), _components.end(),
                                                [componentID] (const auto &component)
                                                {
                                                        return component->getComponentID() == componentID;
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

          [[nodiscard]] ComponentStorage<C> &getComponents()
          {
                  return _components;
          }

          [[nodiscard]] const ComponentStorage<C> &getComponents() const
          {
                  return _components;
          }

  private:
  };

  template <class C>
  std::ostream &operator<<(std::ostream &out, const ComponentContainer<C> &);

}

#endif /* !ECS_COMPONENTCONTAINER_HPP */
