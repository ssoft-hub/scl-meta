#pragma once
#ifndef SCL_UTILITY_SCL_DOES_METHOD_EXIST_H
#define SCL_UTILITY_SCL_DOES_METHOD_EXIST_H

#include <ScL/Meta/Trait/IsDetected.h>
#include <ScL/Utility/SimilarMethod.h>

#define SCL_DOES_METHOD_EXIST( method, Shortname ) \
    template < typename _Type, typename ... _Arguments > \
    using Shortname ## MethodUnstrictOperation = decltype( ::std::declval< _Type >(). method ( ::std::declval< _Arguments >() ... ) ); \
     \
    template < typename _Type, typename ... _Arguments > \
    using Shortname ## StaticMethodStrictOperation = decltype( ::std::integral_constant< Shortname ## MethodUnstrictOperation< _Type, _Arguments ... >(*)( _Arguments ... ), &::std::decay_t< _Type >::method >::value( ::std::declval< _Arguments >() ... ) ); \
     \
    template < typename _Type, typename ... _Arguments > \
    using Shortname ## MethodStrictOperation = decltype( (::std::declval< _Type >() .* ::std::integral_constant< ::ScL::SimilarMethod< _Type, Shortname ## MethodUnstrictOperation< _Type, _Arguments ... >( _Arguments ... ) >, &::std::decay_t< _Type >::foo >::value)( ::std::declval< _Arguments >() ... ) ); \
     \
    template < typename ... _Arguments > \
    static constexpr bool does_ ## method ## _method_exist = ::ScL::Meta::Detector< Shortname ## StaticMethodStrictOperation, _Arguments ... >::isDetected(); \

#endif
