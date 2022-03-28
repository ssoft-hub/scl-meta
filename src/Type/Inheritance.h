#pragma once
#ifndef SCL_META_INHERITED_H

#include "Sequence.h"

namespace ScL { namespace Meta
{
    namespace Detail
    {
        template < typename _Type >
        class Inherited;

        template <> class Inherited< Sequence<> > {};

        template < typename _Type, typename ... _Types >
        class Inherited< Sequence< _Type, _Types ... > >
            : public _Type
            , public Inherited< Sequence< _Types ... > >
        {};
    }
    template < typename _Type >
    using Inherited = Detail::Inherited< _Type >;
}}

#endif
