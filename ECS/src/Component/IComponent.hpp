/*
** EPITECH PROJECT, 2021
** ECS
** File description:
** IComponent
*/

#ifndef ECS_ICOMPONENT_HPP
#define ECS_ICOMPONENT_HPP

#include <ostream>
#include <vector>

#include "../util/util.hpp"

namespace ecs
{
        class IEntity;

        using ComponentID = util::ID;
        using ComponentTypeID = util::ID;

        constexpr ComponentID INVALID_COMPONENT_ID{ util::INVALID_ID };

        class IComponent
        {
                // ATTRIBUTES
            private:
                ComponentID _componentID{ INVALID_COMPONENT_ID };

                static inline ::std::vector<ComponentID> m_freeID{};

                static inline size_t m_componentTypeCount{ 0 };

                NonOwningPointer<IEntity> m_owner{ nullptr };

                bool _active{ true };

            public:
                // METHODS
            public:    // CONSTRUCTORS
                explicit IComponent();
                virtual ~IComponent();
                IComponent(const IComponent &copy) = default;
                IComponent(IComponent &&) noexcept = default;

            public:    // OPERATORS
                IComponent &operator=(const IComponent &other) = default;
                IComponent &operator=(IComponent &&) = default;

            public:
                virtual void setup() = 0;

                [[nodiscard]] static const size_t &get_component_type_count();

                [[nodiscard]] const ComponentID &get_id() const;
                [[nodiscard]] virtual ComponentTypeID get_component_type_id() const = 0;

                IComponent &set_owner(NonOwningPointer<IEntity> entity);
                [[nodiscard]] NonOwningPointer<IEntity> get_owner() const;
                [[nodiscard]] const EntityID &get_owner_id() const;

                IComponent &enable();
                IComponent &disable();
                [[nodiscard]] bool is_enabled() const;

            private:
        };

        template <class C> concept IsComponent = std::is_base_of_v<IComponent, C>;

        ::std::ostream &operator<<(::std::ostream &out, const NonOwningPointer<IComponent>);

}    // namespace ecs

#endif /* !ECS_ICOMPONENT_HPP */
