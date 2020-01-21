//
// Created by tiphaine on 06/04/19.
//

#ifndef ECS_SYSTEM_HPP
# define ECS_SYSTEM_HPP

# include <ostream>
# include "ISystem.hpp"

namespace ecs
{
# define SYSTEM(system) system : public ecs::System<system>

  template <class S>
  class System : public ISystem
  {
// ATTRIBUTES
  private:
  public:
          static inline const SystemTypeID _systemTypeID{util::FamilyTypeID<ISystem>::getTypeID<S>()};

// METHODS:
  public: // CONSTRUCTORS
          explicit System(
                  SYSTEM_PRIORITY priority = SYSTEM_PRIORITY::NORMAL,
                  Interval updateInterval = 10
          )
                  : ISystem(priority, updateInterval)
          {
          }
          ~System() override = default;
          System(const System &copy) = delete;
          System(System &&other) noexcept = delete;

  public: // OPERATORS
          System &operator=(const System &other) = delete;
          System &operator=(System &&other) = delete;

  public:
          [[nodiscard]] SystemTypeID getSystemTypeID() const override
          {
                  return _systemTypeID;
          }
          [[nodiscard]] const char *getSystemTypeName() const override
          {
                  static const char *systemTypeName{typeid(S).name()};

                  return systemTypeName;
          }

          [[deprecated]] [[noreturn]] void preUpdate(Interval deltaTime) override
          {
          }
          [[noreturn]] void update(Interval deltaTime) override
          {
          }
          [[deprecated]] [[noreturn]] void postUpdate(Interval deltaTime) override
          {
          }

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

  template <class S>
  std::ostream &operator<<(std::ostream &out, const System<S> &);

}

#endif //ECS_SYSTEM_HPP
