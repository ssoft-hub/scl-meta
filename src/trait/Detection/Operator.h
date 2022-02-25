#pragma once
#ifndef SCL_UTILITY_DOES_OPERATOR_EXIST_H
#define SCL_UTILITY_DOES_OPERATOR_EXIST_H

#include <ScL/Meta/Trait/IsDetected.h>
#include <ScL/Utility/SimilarMethod.h>
#include <ScL/Utility/SingleArgument.h>

/*
#define SCL_NONESUCH_GLOBAL_STRICT_OPERATION( symbol, Invokable ) \
    template < typename ... _Arguments > \
    using Invokable ## GlobalStrictOperation = decltype( nonesuch__( ::std::declval< _Arguments >() ... ) ); \

#define SCL_BINARY_GLOBAL_STRICT_OPERATION( symbol, Invokable ) \
    template < typename _Left, typename _Right > \
    using Invokable ## GlobalStrictOperation = decltype( (::std::integral_constant< Invokable ## UnstrictOperation< _Left, _Right >(*)( _Left, _Right ), (&operator symbol) >::value)( ::std::declval< _Left >(), ::std::declval< _Right >() ) ); \
*/

#define SCL_PREFIX_UNARY_OPERATION( symbol, Invokable ) \
    template < typename _Right > \
    using Invokable ## UnstrictOperation = decltype( symbol ::std::declval< _Right >() ); \
     \
    template < typename _Right > \
    using Invokable ## MemberStrictOperation = decltype( (::std::declval< _Right >() .* ::std::integral_constant< ::ScL::SimilarMethod< _Right, Invokable ## UnstrictOperation< _Right >() >, (&::std::decay_t< _Right >::operator symbol) >::value)() ); \

#define SCL_POSTFIX_UNARY_OPERATION( symbol, Invokable ) \
    template < typename _Left > \
    using Invokable ## UnstrictOperation = decltype( ::std::declval< _Left >() symbol ); \
     \
    template < typename _Left > \
    using Invokable ## MemberStrictOperation = decltype( (::std::declval< _Left >() .* ::std::integral_constant< ::ScL::SimilarMethod< _Left, Invokable ## UnstrictOperation< _Left >( int ) >, &::std::decay_t< _Left >::operator symbol >::value)( ::std::declval< int >() ) ); \

#define SCL_BINARY_OPERATION( symbol, Invokable ) \
    template < typename _Left, typename _Right > \
    using Invokable ## UnstrictOperation = decltype( ::std::declval< _Left >() symbol ::std::declval< _Right >() ); \
     \
    template < typename _Left, typename _Right > \
    using Invokable ## MemberStrictOperation = decltype( (::std::declval< _Left >() .* ::std::integral_constant< ::ScL::SimilarMethod< _Left, Invokable ## UnstrictOperation< _Left, _Right >( _Right ) >, &::std::decay_t< _Left >::operator symbol >::value)( ::std::declval< _Right >() ) ); \

#define SCL_POSTFIX_OPERATION_WITH_ARGUMENT( symbol, Invokable ) \
    template < typename _Type, typename _Argument > \
    using Invokable ## UnstrictOperation = decltype( ::std::declval< _Type >(). operator symbol ( ::std::declval< _Argument >() ) ); \
     \
    template < typename _Type, typename _Argument > \
    using Invokable ## MemberStrictOperation = decltype( (::std::declval< _Type >() .* ::std::integral_constant< ::ScL::SimilarMethod< _Type, Invokable ## UnstrictOperation< _Type, _Argument >( _Argument ) >, &::std::decay_t< _Type >::operator symbol >::value)( ::std::declval< _Argument >() ) ); \

#define SCL_POSTFIX_OPERATION_WITH_ARGUMENTS( symbol, Invokable ) \
    template < typename _Type, typename ... _Arguments > \
    using Invokable ## UnstrictOperation = decltype( ::std::declval< _Type >(). operator symbol ( ::std::declval< _Arguments >() ... ) ); \
     \
    template < typename _Type, typename ... _Arguments > \
    using Invokable ## MemberStrictOperation = decltype( (::std::declval< _Type >() .* ::std::integral_constant< ::ScL::SimilarMethod< _Type, Invokable ## UnstrictOperation< _Type, _Arguments ... >( _Arguments ... ) >, (&::std::decay_t< _Type >::operator symbol) >::value)( ::std::declval< _Arguments >() ... ) ); \

namespace ScL { namespace Meta
{
    SCL_PREFIX_UNARY_OPERATION( & , AddressOf )
    SCL_PREFIX_UNARY_OPERATION( * , Indirection )
    SCL_POSTFIX_OPERATION_WITH_ARGUMENT( ->*, MemberIndirection )
    SCL_BINARY_OPERATION( SCL_SINGLE_ARG( , ), Comma )

    SCL_POSTFIX_OPERATION_WITH_ARGUMENT( [], SquareBrackets )
    SCL_POSTFIX_OPERATION_WITH_ARGUMENTS( (), RoundBrackets )
    SCL_PREFIX_UNARY_OPERATION( +, PrefixPlus )
    SCL_PREFIX_UNARY_OPERATION( -, PrefixMinus )
    SCL_PREFIX_UNARY_OPERATION( ++, PrefixPlusPlus )
    SCL_PREFIX_UNARY_OPERATION( --, PrefixMinusMinus )
    SCL_PREFIX_UNARY_OPERATION( ~, PrefixBitwiseNot )
    SCL_PREFIX_UNARY_OPERATION( !, PrefixLogicalNot )

    SCL_POSTFIX_UNARY_OPERATION( ++, PostfixPlusPlus )
    SCL_POSTFIX_UNARY_OPERATION( --, PostfixMinusMinus )

    SCL_BINARY_OPERATION( ==, Equal )
    SCL_BINARY_OPERATION( !=, NotEqual )
    SCL_BINARY_OPERATION( <, Less )
    SCL_BINARY_OPERATION( <=, LessOrEqual )
    SCL_BINARY_OPERATION( >, Greater )
    SCL_BINARY_OPERATION( >=, GreaterOrEqual )

    SCL_BINARY_OPERATION( *, Multiply )
    SCL_BINARY_OPERATION( /, Divide )
    SCL_BINARY_OPERATION( %, Modulo )
    SCL_BINARY_OPERATION( +, Addition )
    SCL_BINARY_OPERATION( -, Subtraction )

    SCL_BINARY_OPERATION( <<, ShiftLeft )
    SCL_BINARY_OPERATION( >>, ShiftRight )

    SCL_BINARY_OPERATION( &, BitwiseAnd )
    SCL_BINARY_OPERATION( |, BitwiseOr )
    SCL_BINARY_OPERATION( ^, BitwiseXor )

    SCL_BINARY_OPERATION( &&, LogicalAnd )
    SCL_BINARY_OPERATION( ||, LogicalOr )

    SCL_BINARY_OPERATION( =, Assignment )
    SCL_BINARY_OPERATION( *=, MultiplyAssignment )
    SCL_BINARY_OPERATION( /=, DivideAssignment )
    SCL_BINARY_OPERATION( %=, ModuloAssignment )
    SCL_BINARY_OPERATION( +=, AdditionAssignment )
    SCL_BINARY_OPERATION( -=, SubtractionAssignment )
    SCL_BINARY_OPERATION( <<=, ShiftLeftAssignment )
    SCL_BINARY_OPERATION( >>=, ShiftRightAssignment )
    SCL_BINARY_OPERATION( &=, BitwiseAndAssignment )
    SCL_BINARY_OPERATION( |=, BitwiseOrAssignment )
    SCL_BINARY_OPERATION( ^=, BitwiseXorAssignment )
}}

#endif
