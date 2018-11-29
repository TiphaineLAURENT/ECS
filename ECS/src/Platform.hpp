/*
** EPITECH PROJECT, 2021
** ECS
** File description:
** Platform
*/

#ifndef ECS_PLATFORM_HPP
# define ECS_PLATFORM_HPP

#include <cstddef>
#include <limits>
#include <climits>
#include <stdint-gcc.h>

namespace ecs
{

  using u64 = uint64_t;

  template<typename handle_value_type, size_t version_bits, size_t index_bits>
  union Handle
  {
	  static_assert(sizeof(handle_value_type) * CHAR_BIT >= (version_bits
	                                                         +
	                                                         index_bits),
	                                                         	"Invalid handle layout. More bits used than base value can hold!");

	  using value_type = handle_value_type;

	  static constexpr size_t NUM_VERSION_BITS {version_bits};
	  static constexpr size_t NUM_INDEX_BITS {index_bits};

	  static constexpr value_type MIN_VERSION {0};
	  static constexpr value_type MAX_VERSION {(1U << NUM_VERSION_BITS) - 2U};
	  static constexpr value_type MAX_INDICES {(1U << NUM_INDEX_BITS) - 2U};

	  static constexpr value_type INVALID_HANDLE
		                              {std::numeric_limits<value_type>::max()};

    private:
  	value_type value;

    public:
  	struct
        {
	        value_type index : NUM_INDEX_BITS;
	        value_type version : NUM_VERSION_BITS;
        };

  	Handle() = default;
  	Handle(value_type value)
	        : value(value)
        {}
        Handle(value_type index, value_type version)
	        : index(index), version(version)
        {}

        inline explicit operator value_type() const
        {
	        return value;
        }
  };

  using Handle64 = Handle<u64, 24, 40>;

  using ObjectId = size_t;
  using TypeId = size_t;

  static constexpr ObjectId INVALID_OBJECT_ID =
	                            std::numeric_limits<ObjectId>::max();
  static constexpr TypeId INVALID_TYPE_ID
	                          = std::numeric_limits<TypeId>::max();

}

#endif //ECS_PLATFORM_HPP
