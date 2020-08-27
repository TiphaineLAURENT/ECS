/*
** EPITECH PROJECT, 2021
** ECS
** File description:
** EntityContainer
*/

#ifndef ECS_ENTITYCONTAINER_HPP
#define ECS_ENTITYCONTAINER_HPP

#include <map>
#include <memory>
#include <ostream>
#include <string_view>

#include "IEntityContainer.hpp"

namespace ecs
{
        template <IsEntity E> using EntityMap = std::map<EntityID, std::unique_ptr<E>>;

        template <IsEntity E> using EEntityIterator = typename EntityMap<E>::iterator;

        template <IsEntity E> class EntityContainer : public IEntityContainer
        {
                // ATTRIBUTES
            private:
                EntityMap<E> m_entities{};

            public:
                // METHODS
            public:    // CONSTRUCTORS
                explicit EntityContainer() = default;
                ~EntityContainer() override = default;
                EntityContainer(const EntityContainer &copy) = delete;
                EntityContainer(EntityContainer &&) noexcept = delete;

            public:    // OPERATORS
                EntityContainer &operator=(const EntityContainer &other) = delete;
                EntityContainer &operator=(EntityContainer &&) noexcept = delete;

            public:
                [[nodiscard]] const std::string_view &get_entity_type_name() const override
                {
                        static const std::string_view entityTypeName{ typeid(E).name() };

                        return entityTypeName;
                }

                template <class... ARGS> E &create(ARGS &&... args)
                {
                        auto entity = std::make_unique<E>(std::forward<ARGS>(args)...);
                        auto pointer = entity.get();
                        const auto entityID = entity->get_id();

                        m_entities.insert(std::make_pair(entityID, std::move(entity)));
                        return *pointer;
                }
                [[nodiscard]] E &get_entity(EntityID entityID)
                {
                        return *m_entities[entityID].get();
                }
                [[nodiscard]] EntityMap<E> &get_entities() { return m_entities; }
                [[nodiscard]] const EntityMap<E> &get_entities() const { return m_entities; }
                void erase(EntityID entityId) override { m_entities.erase(entityId); }

                [[nodiscard]] EEntityIterator<E> begin() { return m_entities.begin(); }
                [[nodiscard]] EEntityIterator<E> end() { return m_entities.end(); }

            private:
        };

        template <class E> std::ostream &operator<<(std::ostream &out, const EntityContainer<E> &);

}    // namespace ecs

#endif /* !ECS_ENTITYCONTAINER_HPP */
