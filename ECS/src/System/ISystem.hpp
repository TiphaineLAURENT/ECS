//
// Created by tiphaine on 06/04/19.
//

#ifndef ECS_ISYSTEM_HPP
#define ECS_ISYSTEM_HPP

#include <ostream>
#include <string_view>

#include "../util/util.hpp"

namespace ecs
{
        using SystemTypeID = util::ID;

        enum class SYSTEM_PRIORITY
        {
                LOWEST,
                LOW,
                NORMAL,
                MEDIUM,
                HIGH,
                HIGHEST
        };

        class ISystem
        {
                // ATTRIBUTES
            protected:
                Interval m_timeSinceLastUpdate{ 0 };

                Interval m_updateInterval{ 1 };

                SYSTEM_PRIORITY m_priority{ SYSTEM_PRIORITY::NORMAL };

                bool m_enabled{ true };

                bool m_needUpdate{ true };

                bool m_reserved{ false };

            public:
                friend class MediumSystemManager;

                // METHODS:
            public:    // CONSTRUCTORS
                explicit constexpr ISystem(SYSTEM_PRIORITY priority, Interval updateInterval)
                        : m_updateInterval(updateInterval), m_priority(priority)
                {}
                virtual ~ISystem() = default;
                ISystem(const ISystem &copy) = delete;
                ISystem(ISystem &&other) noexcept = delete;

            public:    // OPERATORS
                ISystem &operator=(const ISystem &other) = delete;
                ISystem &operator=(ISystem &&other) noexcept = delete;

            public:
                [[nodiscard]] virtual SystemTypeID get_system_type_id() const = 0;
                [[nodiscard]] virtual const std::string_view &get_system_type_name() const = 0;

                [[deprecated]] virtual void pre_update(Interval deltaTime) = 0;
                virtual void update(Interval deltaTime) = 0;
                [[deprecated]] virtual void post_update(Interval deltaTime) = 0;

                [[nodiscard]] constexpr bool is_enabled() const { return m_enabled; }
                constexpr void enable() { m_enabled = true; }
                constexpr void disable() { m_enabled = false; }

                [[nodiscard]] constexpr Interval get_update_interval() const { return m_updateInterval; }
                constexpr void set_update_interval(Interval interval) { m_updateInterval = interval; }

                [[nodiscard]] constexpr Interval get_time_since_last_update() const
                {
                        return m_timeSinceLastUpdate;
                }

                [[nodiscard]] constexpr SYSTEM_PRIORITY get_priority() const { return m_priority; }
                constexpr void set_priority(SYSTEM_PRIORITY priority) { m_priority = priority; }
        };

        template <class S> concept IsSystem = std::is_base_of_v<ISystem, S>;

        std::ostream &operator<<(std::ostream &out, const NonOwningPointer<ISystem>);

}    // namespace ecs

#endif    // ECS_ISYSTEM_HPP
