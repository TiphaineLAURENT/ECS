//
// Created by tiphaine on 06/04/19.
//

#ifndef ECS_SIMPLESYSTEMMANAGER_HPP
# define ECS_SIMPLESYSTEMMANAGER_HPP

# include <ostream>
# include <vector>
# include <memory>
# include <map>
# include <list>
# include <algorithm>

# include "../util/util.hpp"
# include "ISystem.hpp"

namespace ecs
{

        class SimpleSystemManager
        {
                // ATTRIBUTES
        private:
                using SystemRegistry = std::map<
                        util::ID,
                        std::unique_ptr<ISystem>
                >;

                SystemRegistry m_systems{};

        public:

                // METHODS:
        public: // CONSTRUCTORS
                SimpleSystemManager() = default;
                ~SimpleSystemManager() = default;
                SimpleSystemManager(const SimpleSystemManager &copy) = delete;
                SimpleSystemManager(SimpleSystemManager &&other) noexcept = delete;

        public: // OPERATORS
                SimpleSystemManager &operator=(const SimpleSystemManager &other) = delete;
                SimpleSystemManager &operator=(SimpleSystemManager &&other) = delete;

        public:
                [[nodiscard]] static SimpleSystemManager &get_instance();

                template <IsSystem S, class ...ARGS>
                static S &create_system(ARGS &&... args)
                {
                        static_assert(
                                std::is_base_of<ISystem, S>::value,
                                "System must be derived from ISystem"
                                );

                        SimpleSystemManager &instance = get_instance();
                        const SystemTypeID systemTypeID = S::m_systemTypeID;

                        auto system = std::make_unique<S>(std::forward<ARGS>(args)...);
                        instance.m_systems[systemTypeID] = std::move(system);

                        return instance.get_system<S>();
                }

                template <IsSystem S>
                [[nodiscard]] static S &get_system()
                {
                        static_assert(
                                std::is_base_of<ISystem, S>::value,
                                "System must be derived from ISystem"
                                );

                        SimpleSystemManager &instance = get_instance();
                        const SystemTypeID systemTypeID = S::m_systemTypeID;

                        return *static_cast<S *>(instance.m_systems[systemTypeID].get());
                }

                template <IsSystem S>
                static S &enable_system()
                {
                        SimpleSystemManager &instance = get_instance();

                        auto system = instance.get_system<S>();
                        system.enable();
                        return system;
                }

                template <IsSystem S>
                static S &disable_system()
                {
                        SimpleSystemManager &instance = get_instance();

                        auto system = instance.get_system<S>();
                        system.disable();
                        return system;
                }

                template <IsSystem S>
                static S &set_system_update_interval(Interval interval)
                {
                        SimpleSystemManager &instance = get_instance();

                        auto system = instance.get_system<S>();
                        system.set_update_interval(interval);
                        return system;
                }

                static void update(Interval deltaTime);

        };

        std::ostream &operator<<(std::ostream &out, const SimpleSystemManager &);

}

#endif //ECS_SIMPLESYSTEMMANAGER_HPP
