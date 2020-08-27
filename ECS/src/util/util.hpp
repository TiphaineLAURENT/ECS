/*
** EPITECH PROJECT, 2021
** ECS
** File description:
** util
*/

#ifndef ECS_UTIL_HPP
#define ECS_UTIL_HPP

#include <cstddef>
#include <iostream>
#include <limits>

//# include "NonOwningPointer.hpp"

namespace ecs
{
        namespace util
        {
                using ID = std::size_t;
                static constexpr ID INVALID_ID = std::numeric_limits<ID>::max();

                template <class T> class FamilyTypeID
                {
                    public:
                        template <class E> static const ID get_type_id()
                        {
                                static const ID typeID{ typeid(E).hash_code() };
                                return typeID;
                        }
                };

        }    // namespace util

        using EntityID = util::ID;
        using Interval = float;
        template <typename Type>
        using NonOwningPointer = Type
                *const;    // TODO: Use std::reference_wrapper instead -
                           // https://en.cppreference.com/w/cpp/utility/functional/reference_wrapper

        template <class Type> void replace_pointer(NonOwningPointer<Type> &current, Type *replacer)
        {
                const_cast<Type *&>(current) = replacer;
        }

}    // namespace ecs

#endif    // ECS_UTIL_HPP
