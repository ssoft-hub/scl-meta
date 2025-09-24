#pragma once
#ifndef SCL_META_INHERITED_H

#include "Sequence.h"

namespace ScL::Meta::Detail
{
    template <typename _Type>
    class Inherited;

    template <>
    class Inherited<Sequence<> >
    {};

    template <typename _Type, typename... _Types>
    class Inherited<Sequence<_Type, _Types...> >
        : public _Type
        , public Inherited<Sequence<_Types...> >
    {};
} // namespace ScL::Meta::Detail

namespace ScL::Meta
{
    template <typename _Type>
    using Inherited = Detail::Inherited<_Type>;
} // namespace ScL::Meta

#endif
