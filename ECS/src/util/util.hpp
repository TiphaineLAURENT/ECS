/*
** EPITECH PROJECT, 2021
** ECS
** File description:
** util
*/

#ifndef ECS_UTIL_HPP
# define ECS_UTIL_HPP

# include <cstddef>
# include <limits>
# include <iostream>

//# include "NonOwningPointer.hpp"

namespace ecs
{
  namespace util
  {

    using ID = size_t;
    static constexpr ID INVALID_ID = std::numeric_limits<ID>::max();

    template <class T>
    class FamilyTypeID
    {
    private:
            static inline ID _maxID{0};

    public:
            template <class E>
            static const ID get_type_id()
            {
                    static const ID _typeID{_maxID++};
                    return _typeID;
            }

            static const ID get_max_id()
            {
                    return _maxID;
            }
    };

  }

  using EntityID = util::ID;
  using Interval = int64_t;
  template <typename Type>
  using NonOwningPointer = Type*const;

  template <class Type>
  void replace_pointer(NonOwningPointer<Type> &current, Type *replacer)
  {
          const_cast<Type*&>(current) = replacer;
  }

}

#endif //ECS_UTIL_HPP
