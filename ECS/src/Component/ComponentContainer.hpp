/*
** EPITECH PROJECT, 2021
** ECS
** File description:
** ComponentContainer
*/

#ifndef ECS_COMPONENTCONTAINER_HPP
#define ECS_COMPONENTCONTAINER_HPP

#include <algorithm>
#include <list>
#include <memory>
#include <ostream>
#include <string_view>
#include <vector>

#include "IComponentContainer.hpp"

namespace ecs
{
        template <IsComponent C> using ComponentStorage = std::vector<std::unique_ptr<C>>;

        template <IsComponent C> using CComponentIterator = typename ComponentStorage<C>::iterator;

        template <IsComponent C> using ComponentView = std::list<C *>;

        template <IsComponent C> class ComponentContainer : public IComponentContainer
        {
                // ATTRIBUTES
            private:
                ComponentStorage<C> m_components{};

            public:
                // METHODS
            public:    // CONSTRUCTORS
                explicit ComponentContainer() = default;
                ~ComponentContainer() override = default;
                ComponentContainer(const ComponentContainer &copy) = delete;
                ComponentContainer(ComponentContainer &&) noexcept = delete;

            public:    // OPERATORS
                ComponentContainer &operator=(const ComponentContainer &other) = delete;
                ComponentContainer &operator=(ComponentContainer &&) noexcept = delete;

            public:
                [[nodiscard]] const std::string_view &get_component_type_name() const override
                {
                        static const std::string_view componentTypeName{ typeid(C).name() };

                        return componentTypeName;
                }

                template <IsComponent Custom = C, class... ARGS>
                NonOwningPointer<Custom> create(NonOwningPointer<IEntity> entity, ARGS &&... args)
                {
                        auto component = std::make_unique<Custom>(std::forward<ARGS>(args)...);
                        auto pointer = component.get();
                        component->set_owner(entity);
                        component->setup();

                        m_components.push_back(std::move(component));
                        return pointer;
                }
                [[nodiscard]] NonOwningPointer<C> get_for_entity(EntityID entityID)
                {
                        auto iter =
                                std::find_if(m_components.begin(),
                                             m_components.end(),
                                             [entityID](const auto &component) {
                                                     return component->get_owner_id() == entityID;
                                             });
                        if (iter != m_components.end())
                        {
                                return iter->get();
                        }
                        return nullptr;
                }
                [[nodiscard]] ComponentView<C> get_components(EntityID entityID)
                {
                        auto components = ComponentView<C>{};

                        for (auto &component : m_components)
                        {
                                if (component->get_owner_id() == entityID)
                                {
                                        components.push_back(component.get());
                                }
                        }

                        return components;
                }
                [[nodiscard]] const ComponentView<C> get_components(EntityID entityID) const
                {
                        auto components = ComponentView<C>{};

                        for (auto &component : m_components)
                        {
                                if (component->get_owner_id() == entityID)
                                {
                                        components.push_back(component.get());
                                }
                        }
                        return components;
                }
                void erase_for_entity(EntityID entityID) override
                {
                        auto toErase =
                                std::remove_if(m_components.begin(),
                                               m_components.end(),
                                               [entityID](const auto &component) {
                                                       return component->get_owner_id() == entityID;
                                               });
                        m_components.erase(toErase);
                }
                void erase(ComponentID componentID) override
                {
                        auto toErase =
                                std::remove_if(m_components.begin(),
                                               m_components.end(),
                                               [componentID](const auto &component) {
                                                       return component->get_id() == componentID;
                                               });
                        m_components.erase(toErase);
                }

                [[nodiscard]] CComponentIterator<C> begin() { return m_components.begin(); }
                [[nodiscard]] CComponentIterator<C> end() { return m_components.end(); }

                [[nodiscard]] ComponentStorage<C> &get_components() { return m_components; }

                [[nodiscard]] const ComponentStorage<C> &get_components() const
                {
                        return m_components;
                }

                [[nodiscard]] size_t size() override { return m_components.size(); }

            private:
        };

        template <class C>
        std::ostream &operator<<(std::ostream &out, const ComponentContainer<C> &);
}    // namespace ecs

#endif /* !ECS_COMPONENTCONTAINER_HPP */
