//
// Created by tiphaine on 06/04/19.
//

#ifndef ECS_SYSTEM_HPP
#define ECS_SYSTEM_HPP

#include <ostream>
#include <string_view>

#include "ISystem.hpp"

namespace ecs
{
#define SYSTEM(system) \
system:                \
    public             \
        ecs::System<system>

        template <class S> class System : public ISystem
        {
                // ATTRIBUTES
            private:
            public:
                static inline const SystemTypeID m_systemTypeID{
                        util::FamilyTypeID<ISystem>::get_type_id<S>()
                };

                // METHODS:
            public:    // CONSTRUCTORS
                explicit System(SYSTEM_PRIORITY priority = SYSTEM_PRIORITY::NORMAL,
                                Interval updateInterval = 1)
                        : ISystem(priority, updateInterval)
                {}
                ~System() override = default;
                System(const System &copy) = delete;
                System(System &&other) noexcept = delete;

            public:    // OPERATORS
                System &operator=(const System &other) = delete;
                System &operator=(System &&other) = delete;

            public:
                [[nodiscard]] SystemTypeID get_system_type_id() const override
                {
                        return m_systemTypeID;
                }
                [[nodiscard]] const std::string_view &get_system_type_name() const override
                {
                        static const std::string_view systemTypeName{ typeid(S).name() };

                        return systemTypeName;
                }

                [[deprecated]] void pre_update(Interval deltaTime) override {}
                void update(Interval deltaTime) override {}
                [[deprecated]] void post_update(Interval deltaTime) override {}

                /*
                template <class ...Dependencies>
                void addDependencies(Dependencies &&... dependencies)
                {
                        SystemManager::addSystemDependency(
                                this,
                                std::forward<Dependencies>(dependencies)...
                        );
                }
                */
        };

        template <class S> std::ostream &operator<<(std::ostream &out, const System<S> &);

}    // namespace ecs

#endif    // ECS_SYSTEM_HPP
