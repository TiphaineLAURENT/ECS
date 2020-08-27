/*
** EPITECH PROJECT, 2021
** ECS
** File description:
** Component
*/

#ifndef ECS_COMPONENT_HPP
#define ECS_COMPONENT_HPP

#include "IComponent.hpp"

namespace ecs
{
#define COMPONENT(component) component: public ecs::Component<component>

        template <class C> class Component : public IComponent
        {
                // ATTRIBUTES
            private:
                static inline ComponentID m_componentCount{ 0 };

            public:
                static inline const ComponentTypeID m_componentTypeID{
                        util::FamilyTypeID<IComponent>::get_type_id<C>()
                };

                // METHODS
            public:    // CONSTRUCTORS
                explicit Component() : IComponent() { ++m_componentCount; }
                ~Component() override { --m_componentCount; }
                Component(const Component &copy) = default;
                Component(Component &&) noexcept = default;

            public:    // OPERATORS
                Component &operator=(const Component &other) = default;
                Component &operator=(Component &&) noexcept = default;

            public:
                void setup() override {}
                [[nodiscard]] static size_t get_component_count() { return m_componentCount; }

                [[nodiscard]] ComponentTypeID get_component_type_id() const override
                {
                        return m_componentTypeID;
                }

            private:
        };

        template <class C> std::ostream &operator<<(std::ostream &out, const Component<C> &);

}    // namespace ecs

#endif /* !ECS_COMPONENT_HPP */
