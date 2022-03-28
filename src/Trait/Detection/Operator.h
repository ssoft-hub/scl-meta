#pragma once
#ifndef SCL_META_UTILITY_DOES_OPERATOR_EXIST_H
#define SCL_META_UTILITY_DOES_OPERATOR_EXIST_H

#include <ScL/Meta/Trait/IsDetected.h>
#include <ScL/Utility/MemberSignature.h>
#include <ScL/Utility/SingleArgument.h>

#define SCL_META_PREFIX_UNARY_OPERATOR_DETECTION( symbol, Invokable ) \
    template < typename _Right > \
    using Invokable ## UnstrictOperation = decltype( symbol ::std::declval< _Right >() ); \
     \
    template < typename _Right > \
    using Invokable ## MemberStrictOperation = decltype( (::std::declval< _Right >() .* ::std::integral_constant< ::ScL::MemberSignature< _Right, Invokable ## UnstrictOperation< _Right >() >, (&::std::decay_t< _Right >::operator symbol) >::value)() ); \

#define SCL_META_POSTFIX_UNARY_OPERATOR_DETECTION( symbol, Invokable ) \
    template < typename _Left > \
    using Invokable ## UnstrictOperation = decltype( ::std::declval< _Left >() symbol ); \
     \
    template < typename _Left > \
    using Invokable ## MemberStrictOperation = decltype( (::std::declval< _Left >() .* ::std::integral_constant< ::ScL::MemberSignature< _Left, Invokable ## UnstrictOperation< _Left >( int ) >, (&::std::decay_t< _Left >::operator symbol) >::value)( ::std::declval< int >() ) ); \

#define SCL_META_BINARY_OPERATOR_DETECTION( symbol, Invokable ) \
    template < typename _Left, typename _Right > \
    using Invokable ## UnstrictOperation = decltype( ::std::declval< _Left >() symbol ::std::declval< _Right >() ); \
     \
    template < typename _Left, typename _Right > \
    using Invokable ## MemberStrictOperation = decltype( (::std::declval< _Left >() .* ::std::integral_constant< ::ScL::MemberSignature< _Left, Invokable ## UnstrictOperation< _Left, _Right >( _Right ) >, (&::std::decay_t< _Left >::operator symbol) >::value)( ::std::declval< _Right >() ) ); \

#define SCL_META_GLOBAL_BINARY_OPERATOR_DETECTION( symbol, Invokable ) \
    template < typename _Left, typename _Right > \
    using Invokable ## GlobalStrictOperation = decltype( (::std::integral_constant< Invokable ## UnstrictOperation< _Left, _Right >(*)( _Left, _Right ), (&operator symbol) >::value)( ::std::declval< _Left >(), ::std::declval< _Right >() ) ); \

#define SCL_META_POSTFIX_OPERATOR_DETECTION_WITH_ARGUMENT( symbol, Invokable ) \
    template < typename _Type, typename _Argument > \
    using Invokable ## UnstrictOperation = decltype( ::std::declval< _Type >(). operator symbol ( ::std::declval< _Argument >() ) ); \
     \
    template < typename _Type, typename _Argument > \
    using Invokable ## MemberStrictOperation = decltype( (::std::declval< _Type >() .* ::std::integral_constant< ::ScL::MemberSignature< _Type, Invokable ## UnstrictOperation< _Type, _Argument >( _Argument ) >, (&::std::decay_t< _Type >::operator symbol) >::value)( ::std::declval< _Argument >() ) ); \

#define SCL_META_POSTFIX_OPERATOR_DETECTION_WITH_ARGUMENTS( symbol, Invokable ) \
    template < typename _Type, typename ... _Arguments > \
    using Invokable ## UnstrictOperation = decltype( ::std::declval< _Type >(). operator symbol ( ::std::declval< _Arguments >() ... ) ); \
     \
    template < typename _Type, typename ... _Arguments > \
    using Invokable ## MemberStrictOperation = decltype( (::std::declval< _Type >() .* ::std::integral_constant< ::ScL::MemberSignature< _Type, Invokable ## UnstrictOperation< _Type, _Arguments ... >( _Arguments ... ) >, (&::std::decay_t< _Type >::operator symbol) >::value)( ::std::declval< _Arguments >() ... ) ); \

namespace ScL { namespace Meta
{
    SCL_META_PREFIX_UNARY_OPERATOR_DETECTION( & , AddressOf )
    SCL_META_PREFIX_UNARY_OPERATOR_DETECTION( * , Indirection )
    SCL_META_POSTFIX_OPERATOR_DETECTION_WITH_ARGUMENT( ->*, MemberIndirection )
    SCL_META_BINARY_OPERATOR_DETECTION( SCL_SINGLE_ARG( , ), Comma )

    SCL_META_POSTFIX_OPERATOR_DETECTION_WITH_ARGUMENT( [], SquareBrackets )
    SCL_META_POSTFIX_OPERATOR_DETECTION_WITH_ARGUMENTS( (), RoundBrackets )
    SCL_META_PREFIX_UNARY_OPERATOR_DETECTION( +, PrefixPlus )
    SCL_META_PREFIX_UNARY_OPERATOR_DETECTION( -, PrefixMinus )
    SCL_META_PREFIX_UNARY_OPERATOR_DETECTION( ++, PrefixPlusPlus )
    SCL_META_PREFIX_UNARY_OPERATOR_DETECTION( --, PrefixMinusMinus )
    SCL_META_PREFIX_UNARY_OPERATOR_DETECTION( ~, PrefixBitwiseNot )
    SCL_META_PREFIX_UNARY_OPERATOR_DETECTION( !, PrefixLogicalNot )

    SCL_META_POSTFIX_UNARY_OPERATOR_DETECTION( ++, PostfixPlusPlus )
    SCL_META_POSTFIX_UNARY_OPERATOR_DETECTION( --, PostfixMinusMinus )

    SCL_META_BINARY_OPERATOR_DETECTION( ==, Equal )
    SCL_META_BINARY_OPERATOR_DETECTION( !=, NotEqual )
    SCL_META_BINARY_OPERATOR_DETECTION( <, Less )
    SCL_META_BINARY_OPERATOR_DETECTION( <=, LessOrEqual )
    SCL_META_BINARY_OPERATOR_DETECTION( >, Greater )
    SCL_META_BINARY_OPERATOR_DETECTION( >=, GreaterOrEqual )

    SCL_META_BINARY_OPERATOR_DETECTION( *, Multiply )
    SCL_META_BINARY_OPERATOR_DETECTION( /, Divide )
    SCL_META_BINARY_OPERATOR_DETECTION( %, Modulo )
    SCL_META_BINARY_OPERATOR_DETECTION( +, Addition )
    SCL_META_BINARY_OPERATOR_DETECTION( -, Subtraction )

    SCL_META_BINARY_OPERATOR_DETECTION( <<, LeftShift )
    SCL_META_BINARY_OPERATOR_DETECTION( >>, RightShift )

    SCL_META_BINARY_OPERATOR_DETECTION( &, BitwiseAnd )
    SCL_META_BINARY_OPERATOR_DETECTION( |, BitwiseOr )
    SCL_META_BINARY_OPERATOR_DETECTION( ^, BitwiseXor )

    SCL_META_BINARY_OPERATOR_DETECTION( &&, LogicalAnd )
    SCL_META_BINARY_OPERATOR_DETECTION( ||, LogicalOr )

    SCL_META_BINARY_OPERATOR_DETECTION( =, Assignment )
    SCL_META_BINARY_OPERATOR_DETECTION( *=, MultiplyAssignment )
    SCL_META_BINARY_OPERATOR_DETECTION( /=, DivideAssignment )
    SCL_META_BINARY_OPERATOR_DETECTION( %=, ModuloAssignment )
    SCL_META_BINARY_OPERATOR_DETECTION( +=, AdditionAssignment )
    SCL_META_BINARY_OPERATOR_DETECTION( -=, SubtractionAssignment )
    SCL_META_BINARY_OPERATOR_DETECTION( <<=, LeftShiftAssignment )
    SCL_META_BINARY_OPERATOR_DETECTION( >>=, RightShiftAssignment )
    SCL_META_BINARY_OPERATOR_DETECTION( &=, BitwiseAndAssignment )
    SCL_META_BINARY_OPERATOR_DETECTION( |=, BitwiseOrAssignment )
    SCL_META_BINARY_OPERATOR_DETECTION( ^=, BitwiseXorAssignment )
}}

#undef SCL_META_PREFIX_UNARY_OPERATOR_DETECTION
#undef SCL_META_POSTFIX_UNARY_OPERATOR_DETECTION
#undef SCL_META_BINARY_OPERATOR_DETECTION
// Must be used after global operator definition
// #undef SCL_META_GLOBAL_BINARY_OPERATOR_DETECTION
#undef SCL_META_POSTFIX_OPERATOR_DETECTION_WITH_ARGUMENT
#undef SCL_META_POSTFIX_OPERATOR_DETECTION_WITH_ARGUMENTS

#endif
