/*
** EPITECH PROJECT, 2021
** ECS
** File description:
** IEntity
*/

#ifndef ECS_IENTITY_HPP
#define ECS_IENTITY_HPP

#include <ostream>
#include <vector>

#include "../Component/ComponentManager.hpp"
#include "../util/util.hpp"

namespace ecs
{
        using EntityID = util::ID;
        constexpr EntityID INVALID_ENTITY_ID = util::INVALID_ID;

        using EntityTypeID = util::ID;

        class IEntity
        {
                // ATTRIBUTES
            private:
                EntityID m_entityID{ INVALID_ENTITY_ID };

                static inline std::vector<EntityID> m_freeID{};

                static inline size_t m_entityCount{ 0 };

                bool m_active{ true };

            public:
                // METHODS
            public:    // CONSTRUCTORS
                explicit IEntity();
                virtual ~IEntity();
                IEntity(const IEntity &copy) = default;
                IEntity(IEntity &&) noexcept = default;

            public:    // OPERATORS
                IEntity &operator=(const IEntity &other) = default;
                IEntity &operator=(IEntity &&) noexcept = default;

            public:
                [[nodiscard]] static EntityID get_entity_count();

                [[nodiscard]] const EntityID &get_id() const;
                [[nodiscard]] virtual EntityTypeID get_entity_type_id() const = 0;

                IEntity &enable();
                IEntity &disable();
                [[nodiscard]] bool is_enabled() const;

                template <IsComponent C, IsComponent Container = C, class... ARGS>
                NonOwningPointer<C> create_component(ARGS &&... args)
                {
                        return ComponentManager::create_component<C, Container>(
                                this, std::forward<ARGS>(args)...);
                }
                template <IsComponent C, IsComponent Container = C>
                [[nodiscard]] NonOwningPointer<C> get_component() const
                {
                        return ComponentManager::get_component<C, Container>(m_entityID);
                }
                template <IsComponent C>[[nodiscard]] ComponentView<C> get_components() const
                {
                        return ComponentManager::get_components<C>(m_entityID);
                }
                template <IsComponent C> void erase_component()
                {
                        ComponentManager::erase_for_entity<C>(m_entityID);
                }

            private:
        };

        template <class E> concept IsEntity = std::is_base_of_v<IEntity, E>;

        std::ostream &operator<<(std::ostream &out, const NonOwningPointer<IEntity>);
}    // namespace ecs

#endif /* !ECS_IENTITY_HPP */
