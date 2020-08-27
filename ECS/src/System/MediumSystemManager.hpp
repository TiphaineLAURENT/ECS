//
// Created by Tiphaine LAURENT on 06/08/2019.
//

#ifndef STARFARM_MEDIUMSYSTEMMANAGER_HPP
#define STARFARM_MEDIUMSYSTEMMANAGER_HPP

#include <algorithm>
#include <map>
#include <memory>
#include <ostream>
#include <vector>

#include "../util/util.hpp"
#include "ISystem.hpp"

namespace ecs
{
        class MediumSystemManager
        {
                // ATTRIBUTES
            private:
                using SystemMap = std::map<util::ID, std::unique_ptr<ISystem>>;

                SystemMap m_systems{};

                std::vector<ISystem *> m_orderedSystems{};

            public:
                // METHODS
            public:    // CONSTRUCTORS
                explicit MediumSystemManager() = default;
                ~MediumSystemManager() = default;
                MediumSystemManager(const MediumSystemManager &copy) = delete;
                MediumSystemManager(MediumSystemManager &&) = delete;

            public:    // OPERATORS
                MediumSystemManager &operator=(const MediumSystemManager &other) = delete;
                MediumSystemManager &operator=(MediumSystemManager &&) = delete;

                [[nodiscard]] NonOwningPointer<ISystem> operator[](size_t index) const
                {
                        if (index < m_orderedSystems.size())
                        {
                                return m_orderedSystems.at(index);
                        }
                        return nullptr;
                }

            public:
                template <IsSystem S, class... ARGS> S &create_system(ARGS &&... args)
                {
                        const auto systemTypeID = S::m_systemTypeID;

                        m_systems.emplace(systemTypeID,
                                          std::make_unique<S>(std::forward<ARGS>(args)...));

                        return get_system<S>();
                }

                void update_systems_order()
                {
                        m_orderedSystems.clear();
                        m_orderedSystems.reserve(m_systems.size());
                        for (auto &[key, system] : m_systems)
                        {
                                if (system->is_enabled())
                                {
                                        m_orderedSystems.emplace_back(system.get());
                                }
                        }
                        std::sort(m_orderedSystems.begin(),
                                  m_orderedSystems.end(),
                                  [](const auto &system1, const auto &system2) {
                                          return system1->get_priority() > system2->get_priority();
                                  });
                }

                template <IsSystem S>[[nodiscard]] S &get_system()
                {
                        const auto systemTypeID = S::m_systemTypeID;
                        return *static_cast<S *>(m_systems[systemTypeID].get());
                }

                template <IsSystem S> static S &enable_system()
                {
                        auto system = get_system<S>();
                        system.enable();
                        return system;
                }

                template <IsSystem S> S &disable_system()
                {
                        auto system = get_system<S>();
                        system.disable();
                        return system;
                }

                template <IsSystem S> S &set_system_update_interval(Interval interval)
                {
                        auto system = get_system<S>();
                        system.set_update_interval(interval);
                        return system;
                }

                template <IsSystem S> S &set_system_priority(SYSTEM_PRIORITY priority)
                {
                        auto system = get_system<S>();
                        system.set_priority(priority);
                        return system;
                }

                void update(Interval deltaTime);

            private:
        };

        std::ostream &operator<<(std::ostream &out, const MediumSystemManager &);

}    // namespace ecs

#endif    // STARFARM_MEDIUMSYSTEMMANAGER_HPP
