#pragma once
#ifndef SCL_UTILITY_DOES_OPERATOR_EXIST_H
#define SCL_UTILITY_DOES_OPERATOR_EXIST_H

#include <ScL/Meta/Trait/IsDetected.h>
#include <ScL/Utility/SimilarMethod.h>
#include <ScL/Utility/SingleArgument.h>

#define SCL_DOES_OPERATOR_EXIST( symbol, Invokable ) \
    template < typename ... _Arguments > \
    /*inline*/ constexpr bool does_ ## Invokable ## _operator_exist = ::ScL::Meta::Detector< Invokable ## UnstrictOperation, _Arguments ... >::isDetected(); \

#define SCL_NONESUCH_GLOBAL_STRICT_OPERATION( symbol, Invokable ) \
    template < typename ... _Arguments > \
    using Invokable ## GlobalStrictOperation = decltype( nonesuch__( ::std::declval< _Arguments >() ... ) ); \

#define SCL_BINARY_GLOBAL_STRICT_OPERATION( symbol, Invokable ) \
    template < typename _Left, typename _Right > \
    using Invokable ## GlobalStrictOperation = decltype( (::std::integral_constant< Invokable ## UnstrictOperation< _Left, _Right >(*)( _Left, _Right ), (&operator symbol) >::value)( ::std::declval< _Left >(), ::std::declval< _Right >() ) ); \

#define SCL_PREFIX_UNARY_OPERATION( symbol, Invokable ) \
    template < typename _Right > \
    using Invokable ## UnstrictOperation = decltype( symbol ::std::declval< _Right >() ); \
     \
    template < typename _Right > \
    using Invokable ## MemberStrictOperation = decltype( (::std::declval< _Right >() .* ::std::integral_constant< ::ScL::SimilarMethod< _Right, Invokable ## UnstrictOperation< _Right >() >, &::std::decay_t< _Right >::operator symbol >::value)() ); \

#define SCL_DOES_PREFIX_UNARY_OPERATOR_EXIST( symbol, Invokable ) \
    SCL_PREFIX_UNARY_OPERATION( SCL_SINGLE_ARG( symbol ), Invokable ) \
    SCL_DOES_OPERATOR_EXIST( SCL_SINGLE_ARG( symbol ), Invokable ) \

#define SCL_POSTFIX_UNARY_OPERATION( symbol, Invokable ) \
    template < typename _Left > \
    using Invokable ## UnstrictOperation = decltype( ::std::declval< _Left >() symbol ); \
     \
    template < typename _Left > \
    using Invokable ## MemberStrictOperation = decltype( (::std::declval< _Left >() .* ::std::integral_constant< ::ScL::SimilarMethod< _Left, Invokable ## UnstrictOperation< _Left >( int ) >, &::std::decay_t< _Left >::operator symbol >::value)( ::std::declval< int >() ) ); \

#define SCL_DOES_POSTFIX_UNARY_OPERATOR_EXIST( symbol, Invokable ) \
    SCL_POSTFIX_UNARY_OPERATION( SCL_SINGLE_ARG( symbol ), Invokable ) \
    SCL_DOES_OPERATOR_EXIST( SCL_SINGLE_ARG( symbol ), Invokable ) \

#define SCL_BINARY_OPERATION( symbol, Invokable ) \
    template < typename _Left, typename _Right > \
    using Invokable ## UnstrictOperation = decltype( ::std::declval< _Left >() symbol ::std::declval< _Right >() ); \
     \
    template < typename _Left, typename _Right > \
    using Invokable ## MemberStrictOperation = decltype( (::std::declval< _Left >() .* ::std::integral_constant< ::ScL::SimilarMethod< _Left, Invokable ## UnstrictOperation< _Left, _Right >( _Right ) >, &::std::decay_t< _Left >::operator symbol >::value)( ::std::declval< _Right >() ) ); \

#define SCL_DOES_BINARY_OPERATOR_EXIST( symbol, Invokable ) \
    SCL_BINARY_OPERATION( SCL_SINGLE_ARG( symbol ), Invokable ) \
    SCL_DOES_OPERATOR_EXIST( SCL_SINGLE_ARG( symbol ), Invokable ) \

#define SCL_POSTFIX_OPERATION_WITH_ARGUMENT( symbol, Invokable ) \
    template < typename _Type, typename _Argument > \
    using Invokable ## UnstrictOperation = decltype( ::std::declval< _Type >(). operator symbol ( ::std::declval< _Argument >() ) ); \
     \
    template < typename _Type, typename _Argument > \
    using Invokable ## MemberStrictOperation = decltype( (::std::declval< _Type >() .* ::std::integral_constant< ::ScL::SimilarMethod< _Type, Invokable ## UnstrictOperation< _Type, _Argument >( _Argument ) >, &::std::decay_t< _Type >::operator symbol >::value)( ::std::declval< _Argument >() ) ); \


#define SCL_DOES_POSTFIX_UNARY_OPERATOR_WITH_ARGUMENT_EXIST_TRAIT( symbol, Invokable ) \
    SCL_POSTFIX_OPERATION_WITH_ARGUMENT( SCL_SINGLE_ARG( symbol ), Invokable ) \
    SCL_DOES_OPERATOR_EXIST( SCL_SINGLE_ARG( symbol ), Invokable ) \

#define SCL_POSTFIX_OPERATION_WITH_ARGUMENTS( symbol, Invokable ) \
    template < typename _Type, typename ... _Arguments > \
    using Invokable ## UnstrictOperation = decltype( ::std::declval< _Type >(). operator symbol ( ::std::declval< _Arguments >() ... ) ); \
     \
    template < typename _Type, typename ... _Arguments > \
    using Invokable ## MemberStrictOperation = decltype( (::std::declval< _Type >() .* ::std::integral_constant< ::ScL::SimilarMethod< _Type, Invokable ## UnstrictOperation< _Type, _Arguments ... >( _Arguments ... ) >, &::std::decay_t< _Type >::operator symbol >::value)( ::std::declval< _Arguments >() ... ) ); \

#define SCL_DOES_POSTFIX_UNARY_OPERATOR_WITH_ARGUMENTS_EXIST_TRAIT( symbol, Invokable ) \
    SCL_POSTFIX_OPERATION_WITH_ARGUMENTS( SCL_SINGLE_ARG( symbol ), Invokable ) \
    SCL_DOES_OPERATOR_EXIST( SCL_SINGLE_ARG( symbol ), Invokable ) \


namespace ScL { namespace Meta
{
    SCL_DOES_PREFIX_UNARY_OPERATOR_EXIST( & , AddressOf )

    SCL_DOES_PREFIX_UNARY_OPERATOR_EXIST( * , Indirection )
    SCL_DOES_POSTFIX_UNARY_OPERATOR_WITH_ARGUMENT_EXIST_TRAIT( ->*, MemberIndirection )
    SCL_DOES_BINARY_OPERATOR_EXIST( SCL_SINGLE_ARG( , ), Comma )

    SCL_DOES_POSTFIX_UNARY_OPERATOR_WITH_ARGUMENT_EXIST_TRAIT( [], SquareBrackets )
    SCL_DOES_POSTFIX_UNARY_OPERATOR_WITH_ARGUMENTS_EXIST_TRAIT( (), RoundBrackets )
    SCL_DOES_PREFIX_UNARY_OPERATOR_EXIST( +, PrefixPlus )
    SCL_DOES_PREFIX_UNARY_OPERATOR_EXIST( -, PrefixMinus )
    SCL_DOES_PREFIX_UNARY_OPERATOR_EXIST( ++, PrefixPlusPlus )
    SCL_DOES_PREFIX_UNARY_OPERATOR_EXIST( --, PrefixMinusMinus )
    SCL_DOES_PREFIX_UNARY_OPERATOR_EXIST( ~, PrefixBitwiseNot )
    SCL_DOES_PREFIX_UNARY_OPERATOR_EXIST( !, PrefixLogicalNot )

    SCL_DOES_POSTFIX_UNARY_OPERATOR_EXIST( ++, PostfixPlusPlus )
    SCL_DOES_POSTFIX_UNARY_OPERATOR_EXIST( --, PostfixMinusMinus )

    SCL_DOES_BINARY_OPERATOR_EXIST( ==, Equal )
    SCL_DOES_BINARY_OPERATOR_EXIST( !=, NotEqual )
    SCL_DOES_BINARY_OPERATOR_EXIST( <, Less )
    SCL_DOES_BINARY_OPERATOR_EXIST( <=, LessOrEqual )
    SCL_DOES_BINARY_OPERATOR_EXIST( >, Greater )
    SCL_DOES_BINARY_OPERATOR_EXIST( >=, GreaterOrEqual )

    SCL_DOES_BINARY_OPERATOR_EXIST( *, Multiply )
    SCL_DOES_BINARY_OPERATOR_EXIST( /, Divide )
    SCL_DOES_BINARY_OPERATOR_EXIST( %, Modulo )
    SCL_DOES_BINARY_OPERATOR_EXIST( +, Addition )
    SCL_DOES_BINARY_OPERATOR_EXIST( -, Subtraction )

    SCL_DOES_BINARY_OPERATOR_EXIST( <<, ShiftLeft )
    SCL_DOES_BINARY_OPERATOR_EXIST( >>, ShiftRight )

    SCL_DOES_BINARY_OPERATOR_EXIST( &, BitwiseAnd )
    SCL_DOES_BINARY_OPERATOR_EXIST( |, BitwiseOr )
    SCL_DOES_BINARY_OPERATOR_EXIST( ^, BitwiseXor )

    SCL_DOES_BINARY_OPERATOR_EXIST( &&, LogicalAnd )
    SCL_DOES_BINARY_OPERATOR_EXIST( ||, LogicalOr )

    SCL_DOES_BINARY_OPERATOR_EXIST( =, Assignment )
    SCL_DOES_BINARY_OPERATOR_EXIST( *=, MultiplyAssignment )
    SCL_DOES_BINARY_OPERATOR_EXIST( /=, DivideAssignment )
    SCL_DOES_BINARY_OPERATOR_EXIST( %=, ModuloAssignment )
    SCL_DOES_BINARY_OPERATOR_EXIST( +=, AdditionAssignment )
    SCL_DOES_BINARY_OPERATOR_EXIST( -=, SubtractionAssignment )
    SCL_DOES_BINARY_OPERATOR_EXIST( <<=, ShiftLeftAssignment )
    SCL_DOES_BINARY_OPERATOR_EXIST( >>=, ShiftRightAssignment )
    SCL_DOES_BINARY_OPERATOR_EXIST( &=, BitwiseAndAssignment )
    SCL_DOES_BINARY_OPERATOR_EXIST( |=, BitwiseOrAssignment )
    SCL_DOES_BINARY_OPERATOR_EXIST( ^=, BitwiseXorAssignment )
}}

#endif
