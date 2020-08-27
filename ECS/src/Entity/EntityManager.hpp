/*
** EPITECH PROJECT, 2021
** ECS
** File description:
** EntityManager
*/

#ifndef ECS_ENTITYMANAGER_HPP
#define ECS_ENTITYMANAGER_HPP

#include <ostream>

#include "EntityContainer.hpp"

namespace ecs
{
        using EntityContainerMap =
                std::unordered_map<EntityTypeID, std::unique_ptr<IEntityContainer>>;

        class EntityManager
        {
                // ATTRIBUTES
            private:
                EntityContainerMap m_containers{};

            public:
                // METHODS
            public:    // CONSTRUCTORS
                explicit constexpr EntityManager() = default;
                ~EntityManager() = default;
                EntityManager(const EntityManager &copy) = delete;
                EntityManager(EntityManager &&) noexcept = delete;

            public:    // OPERATORS
                EntityManager &operator=(const EntityManager &other) = delete;
                EntityManager &operator=(EntityManager &&) = delete;

            public:
                [[nodiscard]] static EntityManager &get_instance();
                template <IsEntity E>
                [[nodiscard]] constexpr static EntityContainer<E> &get_entity_container()
                {
                        const ComponentTypeID entityTypeID = E::m_entityTypeID;
                        EntityManager &instance = get_instance();

                        if (instance.m_containers.find(entityTypeID) == instance.m_containers.end())
                        {
                                auto container = std::make_unique<EntityContainer<E>>();
                                instance.m_containers[entityTypeID] = std::move(container);
                        }

                        return *static_cast<EntityContainer<E> *>(
                                instance.m_containers[entityTypeID].get());
                }

                template <IsEntity E, class... ARGS> static E &create(ARGS &&... args)
                {
                        EntityContainer<E> &container = get_entity_container<E>();

                        return container.create(std::forward<ARGS>(args)...);
                }
                template <IsEntity E>[[nodiscard]] static E &get_entity(EntityID entityID)
                {
                        EntityContainer<E> &container = get_entity_container<E>();

                        return container.get_entity(entityID);
                }
                template <IsEntity E> static void remove_entity(EntityID entityID)
                {
                        EntityContainer<E> &container = get_entity_container<E>();

                        container.erase(entityID);
                }

                template <IsEntity E>[[nodiscard]] static CComponentIterator<E> begin();
                template <IsEntity E>[[nodiscard]] static CComponentIterator<E> end();

            private:
        };

        std::ostream &operator<<(std::ostream &out, const EntityManager &);

}    // namespace ecs

#endif /* !ECS_ENTITYMANAGER_HPP */
