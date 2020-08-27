//
// Created by tiphaine on 06/04/19.
//

#ifndef ECS_SYSTEMMANAGER_HPP
#define ECS_SYSTEMMANAGER_HPP

#include <list>
#include <map>
#include <memory>
#include <ostream>
#include <vector>

#include "../util/util.hpp"
#include "ISystem.hpp"

namespace ecs
{
        using SystemWorkStateMaks = std::vector<bool>;

        class SystemManager
        {
                // ATTRIBUTES
            private:
                using SystemDependencyMatrix = std::vector<std::vector<bool>>;
                using SystemRegistry = std::map<util::ID, std::unique_ptr<ISystem>>;
                using SystemWorkOrder = std::vector<ISystem *>;

                SystemRegistry m_systems{};

                SystemDependencyMatrix m_systemDependencyMatrix{};

                SystemWorkOrder m_systemWorkOrder{};

            public:
                // METHODS:
            public:    // CONSTRUCTORS
                explicit SystemManager() = default;
                ~SystemManager() = default;
                SystemManager(const SystemManager &copy) = delete;
                SystemManager(SystemManager &&other) noexcept = delete;

            public:    // OPERATORS
                SystemManager &operator=(const SystemManager &other) = delete;
                SystemManager &operator=(SystemManager &&other) = delete;

            public:
                [[nodiscard]] static SystemManager &get_instance();

                template <IsSystem S, class... ARGS> static S &create_system(ARGS &&... args)
                {
                        const SystemTypeID systemTypeID = S::m_systemTypeID;
                        SystemManager &instance = get_instance();

                        auto system = std::make_unique<S>(std::forward<ARGS>(args)...);

                        if (systemTypeID + 1 > instance.m_systemDependencyMatrix.size())
                        {
                                instance.m_systemDependencyMatrix.resize(systemTypeID + 1);
                                for (auto &row : instance.m_systemDependencyMatrix)
                                {
                                        row.resize(systemTypeID + 1);
                                }
                        }

                        instance.m_systemWorkOrder.push_back(system.get());
                        instance.m_systems[systemTypeID] = std::move(system);
                        return *static_cast<S *>(instance.m_systems[systemTypeID].get());
                }

                template <IsSystem S, IsSystem D>
                static SystemManager &addSystemDependency(S target, D dependency)
                {
                        SystemTypeID targetTypeID = target.get_system_type_id();
                        SystemTypeID dependencyTypeID = dependency.get_system_type_id();

                        SystemManager &instance = get_instance();
                        instance.m_systemDependencyMatrix[targetTypeID][dependencyTypeID] = true;

                        return instance;
                }

                template <IsSystem S, IsSystem D, class... DS>
                static SystemManager &
                        addSystemDependency(S target, D dependency, DS &&... dependencies)
                {
                        SystemTypeID targetTypeID = target.get_system_type_id();
                        SystemTypeID dependencyTypeID = dependency.get_system_type_id();

                        SystemManager &instance = get_instance();
                        instance.m_systemDependencyMatrix[targetTypeID][dependencyTypeID] = true;

                        return instance.addSystemDependency(target,
                                                            std::forward<DS>(dependencies)...);
                }

                template <IsSystem S>[[nodiscard]] static S &get_system()
                {
                        const SystemTypeID systemTypeID = S::m_systemTypeID;
                        SystemManager &instance = get_instance();

                        return *static_cast<S *>(instance.m_systems[systemTypeID].get());
                }

                template <IsSystem S> static S &enable_system()
                {
                        const SystemTypeID systemTypeID = S::m_systemTypeID;
                        SystemManager &instance = get_instance();

                        auto system = instance.get_system<S>();
                        system.enable();
                        return system;
                }

                template <IsSystem S> static S &disable_system()
                {
                        const SystemTypeID systemTypeID = S::m_systemTypeID;
                        SystemManager &instance = get_instance();

                        auto system = instance.get_system<S>();
                        system.disable();
                        return system;
                }

                template <IsSystem S> static S &set_system_update_interval(Interval interval)
                {
                        const SystemTypeID systemTypeID = S::m_systemTypeID;
                        SystemManager &instance = get_instance();

                        auto system = instance.get_system<S>();
                        system.set_update_interval(interval);
                        return system;
                }

                template <IsSystem S> static S &set_system_priority(SYSTEM_PRIORITY priority)
                {
                        const SystemTypeID systemTypeID = S::m_systemTypeID;
                        SystemManager &instance = get_instance();

                        auto system = instance.get_system<S>();
                        system.set_priority(priority);
                        return system;
                }

                static SystemWorkStateMaks getSystemWorkState();
                static void setSystemWorkState(SystemWorkStateMaks);

                template <class... ActiveSystems>
                static SystemWorkStateMaks
                        generateActiveSystemWorkState(ActiveSystems &&... activeSystems)
                {
                        SystemManager &instance = get_instance();

                        SystemWorkStateMaks mask(instance.m_systemWorkOrder.size(), false);
                        std::list<ISystem *> as{ activeSystems... };
                        for (auto &system : as)
                        {
                                for (size_t i = 0; i < instance.m_systemWorkOrder.size(); ++i)
                                {
                                        if (instance.m_systemWorkOrder[i]->get_system_type_id()
                                            == system->get_system_type_id())
                                        {
                                                mask[i] = true;
                                                break;
                                        }
                                }
                        }

                        return mask;
                }

                static void updateSystemWorkOrder();
                static void update();
        };

        std::ostream &operator<<(std::ostream &out, const SystemManager &);

}    // namespace ecs

#endif    // ECS_SYSTEMMANAGER_HPP
