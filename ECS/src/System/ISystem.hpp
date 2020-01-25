//
// Created by tiphaine on 06/04/19.
//

#ifndef ECS_ISYSTEM_HPP
# define ECS_ISYSTEM_HPP

# include <ostream>

# include "../util/util.hpp"

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
          Interval _timeSinceLastUpdate{0};

          Interval _updateInterval{1};

          SYSTEM_PRIORITY _priority{SYSTEM_PRIORITY::NORMAL};

          bool _enabled{true};

          bool _needUpdate{true};

          bool _reserved{false};

  public:
          friend class MediumSystemManager;

// METHODS:
  public: // CONSTRUCTORS
          explicit ISystem(
                  SYSTEM_PRIORITY,
                  Interval updateInterval
          );
          virtual ~ISystem() = default;
          ISystem(const ISystem &copy) = delete;
          ISystem(ISystem &&other) noexcept = delete;

  public: // OPERATORS
          ISystem &operator=(const ISystem &other) = delete;
          ISystem &operator=(ISystem &&other) noexcept = delete;

  public:
          [[nodiscard]] virtual SystemTypeID get_system_type_id() const = 0;
          [[nodiscard]] virtual const std::string &get_system_type_name() const = 0;

          [[deprecated]] virtual void pre_update(Interval deltaTime) = 0;
          virtual void update(Interval deltaTime) = 0;
          [[deprecated]] virtual void post_update(Interval deltaTime) = 0;

          [[nodiscard]] bool is_enabled() const
          {
                  return _enabled;
          }
          void enable()
          {
                  _enabled = true;
          }
          void disable()
          {
                  _enabled = false;
          }

          [[nodiscard]] Interval get_update_interval() const
          {
                  return _updateInterval;
          }
          void set_update_interval(Interval interval)
          {
                  _updateInterval = interval;
          }

          [[nodiscard]] Interval get_time_since_last_update() const
          {
                  return _timeSinceLastUpdate;
          }

          [[nodiscard]] SYSTEM_PRIORITY get_priority() const
          {
                  return _priority;
          }
          void set_priority(SYSTEM_PRIORITY priority)
          {
                  _priority = priority;
          }

  };

  std::ostream &operator<<(std::ostream &out, const NonOwningPointer<ISystem>);

}

#endif //ECS_ISYSTEM_HPP
