#pragma once
#ifndef SCL_UTILITY_SCL_DOES_METHOD_EXIST_H
#define SCL_UTILITY_SCL_DOES_METHOD_EXIST_H

#include <ScL/Meta/Trait/IsDetected.h>
#include <ScL/Utility/MemberSignature.h>

#define SCL_META_METHOD_DETECTION( method, Shortname ) \
    template < typename _Type, typename ... _Arguments > \
    using Shortname ## MethodUnstrictOperation = decltype( ::std::declval< _Type >(). method ( ::std::declval< _Arguments >() ... ) ); \
     \
    template < typename _Type, typename ... _Arguments > \
    using Shortname ## MethodStrictOperation = decltype( (::std::declval< _Type >() .* ::std::integral_constant< ::ScL::MemberSignature< _Type, Shortname ## MethodUnstrictOperation< _Type, _Arguments ... >( _Arguments ... ) >, \
        (::ScL::MemberSignature< _Type, Shortname ## MethodUnstrictOperation< _Type, _Arguments ... >( _Arguments ... ) >)(&::std::decay_t< _Type >::method) >::value)( ::std::declval< _Arguments >() ... ) ); \
     \
    template < typename _Type, typename ... _Arguments > \
    using Shortname ## StaticMethodStrictOperation = decltype( ::std::integral_constant< Shortname ## MethodUnstrictOperation< _Type, _Arguments ... >(*)( _Arguments ... ), \
        (Shortname ## MethodUnstrictOperation< _Type, _Arguments ... >(*)( _Arguments ... ))(&::std::decay_t< _Type >::method) >::value( ::std::declval< _Arguments >() ... ) ); \

#endif
