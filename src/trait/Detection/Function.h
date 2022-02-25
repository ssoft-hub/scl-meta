#pragma once
#ifndef SCL_UTILITY_DOES_FUNCTION_EXIST_H
#define SCL_UTILITY_DOES_FUNCTION_EXIST_H

#include <ScL/Meta/Trait/IsDetected.h>

#define SCL_DOES_FUNCTION_EXIST( function, Shortname ) \
    template < typename ... _Arguments > \
    using Shortname ## FunctionUnstrictOperation = decltype( function( ::std::declval< _Arguments >() ... ) ); \
     \
    template < typename ... _Arguments > \
    using Shortname ## FunctionStrictOperation = decltype( ::std::integral_constant< FooFunctionUnstrictOperation< _Arguments ... >(*)( _Arguments ... ), &function >::value( ::std::declval< _Arguments >() ... ) ); \

#endif
