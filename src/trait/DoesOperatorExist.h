#pragma once
#ifndef SCL_UTILITY_DOES_OPERATOR_EXIST_H
#define SCL_UTILITY_DOES_OPERATOR_EXIST_H

#include <type_traits>

#define SCL_DOES_PREFIX_UNARY_OPERATOR_EXIST_TRAIT( symbol, Invokable ) \
    template < typename _Right > \
    class Does ## Invokable ## OperatorExistHelper \
    { \
        static_assert( ::std::is_reference< _Right >::value, \
            "The template parameter _Right must to be a reference type." ); \
        template < typename _RightArg, \
            typename = decltype( symbol ::std::declval< _RightArg >() ) > \
        static ::std::true_type __test ( int ); \
    \
        template < typename > \
        static ::std::false_type __test ( ... ); \
    \
    public: \
        using Type = decltype( __test< _Right >( ::std::declval< int >() ) ); \
    }; \
    \
    template < typename _Type > \
    using Does ## Invokable ## OperatorExist = typename Does ## Invokable ## OperatorExistHelper< _Type >::Type; \
    template < typename _Type > \
    /*inline*/ constexpr bool does_ ## Invokable ## _operator_exist = Does ## Invokable ## OperatorExist< _Type >::value; \
    template < typename _Type > \
    inline constexpr bool does ## Invokable ## OperatorExist () { return Does ## Invokable ## OperatorExist< _Type >::value; } \

#define SCL_DOES_POSTFIX_UNARY_OPERATOR_EXIST_TRAIT( symbol, Invokable ) \
    template < typename _Left > \
    class Does ## Invokable ## OperatorExistHelper \
    { \
        static_assert( ::std::is_reference< _Left >::value, \
            "The template parameter _Left must to be a reference type." ); \
        template < typename _LeftArg, \
            typename = decltype( ::std::declval< _LeftArg >() symbol ) > \
        static ::std::true_type __test ( int ); \
    \
        template < typename > \
        static ::std::false_type __test ( ... ); \
    \
    public: \
        using Type = decltype( __test< _Left >( ::std::declval< int >() ) ); \
    }; \
    \
    template < typename _Type > \
    using Does ## Invokable ## OperatorExist = typename Does ## Invokable ## OperatorExistHelper< _Type >::Type; \
    template < typename _Type > \
    /*inline*/ constexpr bool does_ ## Invokable ## _operator_exist = Does ## Invokable ## OperatorExist< _Type >::value; \
    template < typename _Type > \
    inline constexpr bool does ## Invokable ## OperatorExist () { return Does ## Invokable ## OperatorExist< _Type >::value; } \

#define SCL_DOES_BINARY_OPERATOR_EXIST_TRAIT( symbol, Invokable ) \
    template < typename _Left, typename _Right > \
    class Does ## Invokable ## OperatorExistHelper \
    { \
        static_assert( ::std::is_reference< _Right >::value, \
            "The template parameter _Right must to be a reference type." ); \
        static_assert( ::std::is_reference< _Left >::value, \
            "The template parameter _Left must to be a reference type." ); \
        template < typename _LeftArg, typename _RightArg, \
            typename = decltype( ::std::declval< _LeftArg >() symbol ::std::declval< _RightArg >() ) > \
        static ::std::true_type __test ( int ); \
    \
        template < typename, typename > \
        static ::std::false_type __test ( ... ); \
    \
    public: \
        using Type = decltype( __test< _Left, _Right >( ::std::declval< int >() ) ); \
    }; \
    \
    template < typename _Left, typename _Right > \
    using Does ## Invokable ## OperatorExist = typename Does ## Invokable ## OperatorExistHelper< _Left, _Right >::Type; \
    template < typename _Left, typename _Right > \
    /*inline*/ constexpr bool does_ ## Invokable ## _operator_exist = Does ## Invokable ## OperatorExist< _Left, _Right >::value; \
    template < typename _Left, typename _Right > \
    inline constexpr bool does ## Invokable ## OperatorExist () { return Does ## Invokable ## OperatorExist< _Left, _Right >::value; } \

#define SCL_DOES_POSTFIX_UNARY_OPERATOR_WITH_ARGUMENT_EXIST_TRAIT( symbol, Invokable ) \
    template < typename _Type, typename _Argument > \
    class Does ## Invokable ## OperatorExistHelper \
    { \
        template < typename _TypeArg, typename _Arg, \
            typename = decltype( ::std::declval< _TypeArg >(). operator symbol ( ::std::declval< _Arg >() ) ) > \
        static ::std::true_type __test ( int ); \
    \
        template < typename, typename > \
        static ::std::false_type __test ( ... ); \
    \
    public: \
        using Type = decltype( __test< _Type, _Argument >( ::std::declval< int >() ) ); \
    }; \
    \
    template < typename _Type, typename _Argument > \
    using Does ## Invokable ## OperatorExist = typename Does ## Invokable ## OperatorExistHelper< _Type, _Argument >::Type; \
    template < typename _Type, typename _Argument > \
    /*inline*/ constexpr bool does_ ## Invokable ## _operator_exist = Does ## Invokable ## OperatorExist< _Type, _Argument >::value; \
    template < typename _Type, typename _Argument > \
    inline constexpr bool does ## Invokable ## OperatorExist () { return Does ## Invokable ## OperatorExist< _Type, _Argument >::value; } \

#define SCL_DOES_POSTFIX_UNARY_OPERATOR_WITH_ARGUMENTS_EXIST_TRAIT( symbol, Invokable ) \
    template < typename _Type, typename ... _Arguments > \
    class Does ## Invokable ## OperatorExistHelper \
    { \
        template < typename _TypeArg, typename ... _Args, \
            typename = decltype( ::std::declval< _TypeArg >(). operator symbol ( ::std::declval< _Args >() ... ) ) > \
        static ::std::true_type __test ( int ); \
    \
        template < typename, typename ... > \
        static ::std::false_type __test ( ... ); \
    \
    public: \
        using Type = decltype( __test< _Type, _Arguments ... >( ::std::declval< int >() ) ); \
    }; \
    \
    template < typename _Type, typename ... _Arguments > \
    using Does ## Invokable ## OperatorExist = typename Does ## Invokable ## OperatorExistHelper< _Type, _Arguments ... >::Type; \
    template < typename _Type, typename ... _Arguments > \
    /*inline*/ constexpr bool does_ ## Invokable ## _operator_exist = Does ## Invokable ## OperatorExist< _Type, _Arguments ... >::value; \
    template < typename _Type, typename ... _Arguments > \
    inline constexpr bool does ## Invokable ## OperatorExist () { return Does ## Invokable ## OperatorExist< _Type, _Arguments ... >::value; } \

#endif
