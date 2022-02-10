#pragma once
#ifndef SCL_UTILITY_SCL_DOES_METHOD_EXIST_H
#define SCL_UTILITY_SCL_DOES_METHOD_EXIST_H

#include <type_traits>

#define SCL_DOES_METHOD_EXIST_TRAIT( method ) \
    template < typename _Type, typename ... _Arguments > \
    struct Does_ ## method ## _MethodExistHelper \
    { \
    private: \
        template < typename _Test, \
            typename = decltype( ::std::declval< _Test >(). method ( ::std::declval< _Arguments >() ... ) ) > \
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
    struct Does_ ## method ## _MethodExistHelper< _Type, _Result( _Arguments ... ) > \
    { \
    private: \
        template < typename _Test, \
            typename = ::std::enable_if_t< ::std::is_same< decltype( ::std::declval< _Test >(). method ( ::std::declval< _Arguments >() ... ) ), _Result >::value > > \
        static constexpr ::std::true_type __test ( int ); \
    \
        template< typename > \
        static constexpr ::std::false_type __test( ... ); \
    \
    public: \
        using Type = decltype( __test< _Type >( ::std::declval< int >() ) ); \
    }; \
    \
    template < typename _Type, typename ... _Arguments > \
    using Does_ ## method ## _MethodExist = typename Does_ ## method ## _MethodExistHelper< _Type, _Arguments ... >::Type; \
    template < typename _Type, typename ... _Arguments > \
    static constexpr bool does_ ## method ## _method_exist = Does_ ## method ## _MethodExist< _Type, _Arguments ... >::value; \
    template < typename _Type, typename ... _Arguments > \
    static constexpr bool does_ ## method ## _MethodExist () { return Does_ ## method ## _MethodExist< _Type, _Arguments ... >::value; } \

#endif
