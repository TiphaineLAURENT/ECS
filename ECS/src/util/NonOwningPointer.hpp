//
//
//

#ifndef ECS_NONOWNINGPOINTER_HPP
# define ECS_NONOWNINGPOINTER_HPP

# include <type_traits>

namespace ecs
{

        template <class Type>
        class NonOwningPointer
        {
                Type *_pointer{nullptr};

        public:
                NonOwningPointer(Type *t)
                        : _pointer{t}
                {}

                typename std::add_lvalue_reference<Type>::type operator*() const
                {
                        return *_pointer;
                }

                Type *operator->() const noexcept
                {
                        return _pointer;
                }

                void replace(Type *p) noexcept
                {
                        _pointer = p;
                }

                void replace(NonOwningPointer<Type> nop)
                {
                        _pointer = nop._pointer;
                }

                template <class Other>
                bool operator==(const Other *p)
                {
                        return _pointer == p;
                }
                template <class Other>
                bool operator==(const NonOwningPointer<Other> &p)
                {
                        return _pointer == p._pointer;
                }
                bool operator==(nullptr_t) const noexcept
                {
                        return _pointer == nullptr;
                }

                template <class Other>
                bool operator!=(const Other *p)
                {
                        return !(_pointer == p);
                }
                template <class Other>
                bool operator!=(const NonOwningPointer<Other> &p)
                {
                        return !(_pointer == p._pointer);
                }
                bool operator!=(nullptr_t) const noexcept
                {
                        return !(_pointer == nullptr);
                }
        };

}

#endif /* !ECS_NONOWNINGPOINTER_HPP */