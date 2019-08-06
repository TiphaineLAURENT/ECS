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
          float _timeSinceLastUpdate = 0.;

          float _updateInterval = 1.;

          SYSTEM_PRIORITY _priority = SYSTEM_PRIORITY::NORMAL;

          bool _enabled = true;

          bool _needUpdate = true;

          bool _reserved = false;

  public:
          friend class MediumSystemManager;

// METHODS:
  public: // CONSTRUCTORS
          explicit ISystem(
                  SYSTEM_PRIORITY,
                  float
          );
          virtual ~ISystem() = default;
          ISystem(const ISystem &copy) = delete;
          ISystem(ISystem &&other) noexcept = delete;

  public: // OPERATORS
          ISystem &operator=(const ISystem &other) = delete;
          ISystem &operator=(ISystem &&other) noexcept = delete;

  public:
          [[nodiscard]] virtual SystemTypeID getSystemTypeID() const = 0;
          [[nodiscard]] virtual const char *getSystemTypeName() const = 0;

          [[deprecated]] virtual void preUpdate(float deltaTime) = 0;
          virtual void update(float deltaTime) = 0;
          [[deprecated]] virtual void postUpdate(float deltaTime) = 0;

          [[nodiscard]] bool isEnable() const
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

          [[nodiscard]] float getUpdateInterval() const
          {
                  return _updateInterval;
          }
          void setUpdateInterval(float interval)
          {
                  _updateInterval = interval;
          }

          [[nodiscard]] float getTimeSinceLastUpdate() const
          {
                  return _timeSinceLastUpdate;
          }

          [[nodiscard]] SYSTEM_PRIORITY getPriority() const
          {
                  return _priority;
          }
          void setPriority(SYSTEM_PRIORITY priority)
          {
                  _priority = priority;
          }

  };

  std::ostream &operator<<(std::ostream &out, const ISystem *);

}

#endif //ECS_ISYSTEM_HPP
