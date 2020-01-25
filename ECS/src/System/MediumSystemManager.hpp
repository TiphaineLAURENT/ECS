//
// Created by Tiphaine LAURENT on 06/08/2019.
//

#ifndef STARFARM_MEDIUMSYSTEMMANAGER_HPP
#define STARFARM_MEDIUMSYSTEMMANAGER_HPP

# include <ostream>
# include <map>
# include <algorithm>
# include <memory>
# include <vector>

# include "../util/util.hpp"
# include "ISystem.hpp"


namespace ecs
{

  class MediumSystemManager
  {
// ATTRIBUTES
  private:
          using SystemMap = std::map<
                  util::ID,
                  std::unique_ptr<ISystem>>;

          SystemMap _systems{};

          std::vector<ISystem*> _orderedSystems{};

  public:

// METHODS
  public:// CONSTRUCTORS
          MediumSystemManager() = default;
          ~MediumSystemManager() = default;
          MediumSystemManager(const MediumSystemManager &copy) = delete;
          MediumSystemManager(MediumSystemManager &&) = delete;

  public: //OPERATORS
          MediumSystemManager &operator=(const MediumSystemManager &other) = delete;
          MediumSystemManager &operator=(MediumSystemManager &&) = delete;

          [[nodiscard]] NonOwningPointer<ISystem> operator[](size_t index) const
          {
                  if (index < _orderedSystems.size())
                  {
                          return _orderedSystems[index];
                  }
                  return nullptr;
          }

  public:
          template <class S, class ...ARGS>
          S &createSystem(ARGS &&... args)
          {
                  static_assert(
                          std::is_base_of_v<ISystem, S>,
                          "System must be derived from ISystem"
                          );

                  const auto systemTypeID = S::_systemTypeID;

                  _systems.emplace(
                          systemTypeID,
                          std::make_unique<S>(std::forward<ARGS>(args)...)
                  );

                  return getSystem<S>();
          }

          void updateSytemsOrder()
          {
                  _orderedSystems.clear();
                  _orderedSystems.reserve(_systems.size());
                  for (auto &pair : _systems)
                  {
                          if (pair.second->is_enabled())
                          {
                                  _orderedSystems
                                          .emplace_back(pair.second.get());
                          }
                  }
                  std::sort(
                          _orderedSystems.begin(), _orderedSystems.end(),
                          [] (const auto &system1, const auto &system2)
                          {
                                  return system1->get_priority() >
                                          system2->get_priority();
                          }
                  );
          }

          template <class S>
          [[nodiscard]] S &getSystem()
          {
                  static_assert(
                          std::is_base_of_v<ISystem, S>,
                          "System must be derived from ISystem"
                  );

                  const auto systemTypeID = S::_systemTypeID;
                  return *static_cast<S*>(_systems[systemTypeID].get());
          }

          template <class S>
          static S &enableSystem()
          {
                  auto system = getSystem<S>();
                  system.enable();
                  return system;
          }

          template <class S>
          S &disableSystem()
          {
                  auto system = getSystem<S>();
                  system.disable();
                  return system;
          }

          template <class S>
          S &setSystemUpdateInterval(Interval interval)
          {
                  auto system = getSystem<S>();
                  system.set_update_interval(interval);
                  return system;
          }

          template <class S>
          S &setSystemPriority(SYSTEM_PRIORITY priority)
          {
                  auto system = getSystem<S>();
                  system.set_priority(priority);
                  return system;
          }

          void update(Interval deltaTime);

  private:
  };

  std::ostream &operator<<(std::ostream &out, const MediumSystemManager &);

}

#endif //STARFARM_MEDIUMSYSTEMMANAGER_HPP
