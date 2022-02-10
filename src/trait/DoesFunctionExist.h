#pragma once
#ifndef SCL_UTILITY_DOES_FUNCTION_EXIST_H
#define SCL_UTILITY_DOES_FUNCTION_EXIST_H

#include <type_traits>

#define SCL_DOES_FUNCTION_EXIST_TRAIT( function, shortname ) \
    template < typename _Type, typename ... _Arguments > \
    struct Does_ ## shortname ## _FunctionExistHelper { \
    private: \
        template < typename _Test, \
            typename = decltype( function( ::std::declval< _Arguments >() ... ) ) > \
        static constexpr ::std::true_type __test ( int ); \
    \
        template< typename > \
        static constexpr ::std::false_type __test( ... ); \
    \
    public: \
        using Type = decltype( __test< _Type >( ::std::declval< int >() ) ); \
    }; \
    \
    template < typename _Type, typename _Result, typename ... _Arguments > \
    struct Does_ ## shortname ## _FunctionExistHelper< _Type, _Result( _Arguments ... ) > \
    { \
    private: \
        template < typename _Test, \
            typename = ::std::enable_if_t< ::std::is_same< decltype( function( ::std::declval< _Arguments >() ... ) ), _Result >::value > > \
        static constexpr ::std::true_type __test ( int ); \
    \
        template< typename > \
        static constexpr ::std::false_type __test( ... ); \
    \
    public: \
        using Type = decltype( __test< _Type >( ::std::declval< int >() ) ); \
    }; \
    \
    template < typename ... _Arguments > \
    using Does_ ## shortname ## _FunctionExist = typename Does_ ## shortname ## _FunctionExistHelper< void, _Arguments ... >::Type; \
    template < typename ... _Arguments > \
    /*inline*/ constexpr bool does_ ## shortname ## _function_exist = Does_ ## shortname ## _FunctionExist< void, _Arguments ... >::value; \
    template < typename ... _Arguments > \
    inline constexpr bool does ## shortname ## FunctionExist () { return Does_ ## shortname ## _FunctionExist< void, _Arguments ... >::value; } \

#endif
