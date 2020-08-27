/*
** EPITECH PROJECT, 2021
** ECS
** File description:
** ComponentManager
*/

#ifndef ECS_COMPONENTMANAGER_HPP
#define ECS_COMPONENTMANAGER_HPP

#include <ostream>
#include <unordered_map>

#include "ComponentContainer.hpp"

namespace ecs
{
        using ComponentContainerMap =
                std::unordered_map<ComponentTypeID, std::unique_ptr<IComponentContainer>>;

        class ComponentManager
        {
                // ATTRIBUTES
            private:
                ComponentContainerMap m_containers{};

            public:
                // METHODS
            public:    // CONSTRUCTORS
                explicit constexpr ComponentManager() = default;
                ~ComponentManager() = default;
                ComponentManager(const ComponentManager &copy) = delete;
                ComponentManager(ComponentManager &&) noexcept = delete;

            public:    // OPERATORS
                ComponentManager &operator=(const ComponentManager &other) = delete;
                ComponentManager &operator=(ComponentManager &&) = delete;

            public:
                [[nodiscard]] static ComponentManager &get_instance();
                template <IsComponent C> static auto &get_component_container()
                {
                        auto &instance = get_instance();

                        auto container = instance.get_container<C>();
                        if (container == nullptr)
                        {
                                return *instance.create_container<C>();
                        }
                        return *container;
                }

                template <IsComponent C, IsComponent Container = C, class... ARGS>
                static NonOwningPointer<C> create_component(NonOwningPointer<IEntity> entity,
                                                            ARGS &&... args)
                {
                        if constexpr (std::is_same_v<C, Container>)
                        {
                                auto &container = get_component_container<C>();
                                return container.create(entity, std::forward<ARGS>(args)...);
                        }
                        else
                        {
                                auto &container = get_component_container<Container>();
                                return container.template create<C>(entity,
                                                                    std::forward<ARGS>(args)...);
                        }
                }
                template <IsComponent C, IsComponent Container = C>
                [[nodiscard]] static NonOwningPointer<C> get_component(EntityID entityID)
                {
                        auto &container = get_component_container<Container>();

                        return container.get_for_entity(entityID);
                }
                template <IsComponent C>
                [[nodiscard]] static ComponentView<C> get_components(EntityID entityID)
                {
                        auto &container = get_component_container<C>();

                        return container.get_components(entityID);
                }
                template <IsComponent C> static void erase_for_entity(EntityID entityID)
                {
                        auto &container = get_component_container<C>();

                        container.erase_for_entity(entityID);
                }

                template <IsComponent C>[[nodiscard]] static CComponentIterator<C> begin()
                {
                        return get_component_container<C>().begin();
                }
                template <IsComponent C>[[nodiscard]] static CComponentIterator<C> end()
                {
                        return get_component_container<C>().end();
                }

                [[nodiscard]] size_t get_container_count() const { return m_containers.size(); }

            private:
                template <IsComponent C> NonOwningPointer<ComponentContainer<C>> create_container()
                {
                        const auto componentTypeID = C::m_componentTypeID;
                        auto container = std::make_unique<ComponentContainer<C>>();
                        auto pointer = container.get();
                        m_containers[componentTypeID] = std::move(container);

                        return pointer;
                }

                template <IsComponent C>
                [[nodiscard]] NonOwningPointer<ComponentContainer<C>> get_container()
                {
                        const auto componentTypeID = C::m_componentTypeID;
                        auto it = m_containers.find(componentTypeID);
                        if (it != m_containers.end())
                        {
                                return static_cast<ComponentContainer<C> *>(it->second.get());
                        }
                        return nullptr;
                }
        };

        std::ostream &operator<<(std::ostream &out, const ComponentManager &);

}    // namespace ecs

#endif /* !ECS_COMPONENTMANAGER_HPP */
