// This file contanes the implementation of C++ Standard Proposal N4502
// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2015/n4502.pdf
#pragma once
#ifndef SCL_META_IS_DETECTED_H
#define SCL_META_IS_DETECTED_H

#include <type_traits>

namespace ScL { namespace Meta { namespace Detail
{
    struct Nonesuch
    {
        ~Nonesuch () = delete;
        Nonesuch ( Nonesuch const & ) = delete;
        void operator = ( Nonesuch const & ) = delete;
    };

    template < typename _Default, typename _AlwaysVoid, template< typename ... > class _Operation, typename ... _Arguments >
    struct Detector
    {
        using Result = ::std::false_type;
        using Type = _Default;
    };

    template < typename _Default, template< typename ... > class _Operation, typename ... _Arguments >
    struct Detector< _Default, ::std::void_t< _Operation< _Arguments ... > >, _Operation, _Arguments ... >
    {
        using Result = ::std::true_type;
        using Type = _Operation< _Arguments ... >;
    };
}}}

namespace ScL { namespace Meta
{
    template < template < typename ... > class _Operation, typename ... _Arguments >
    using Detected = typename ::ScL::Meta::Detail::Detector< ::ScL::Meta::Detail::Nonesuch, void, _Operation, _Arguments ... >;
        /*!<
         * Тип является вариантом типа Detector с вложеными типами Result и Type, представляющими результат операции, определяемой типом _Operation с аргументами _Arguments.
         * Result - логический тип, который отражает наличие или отсутствие операции, определяемой типом _Operation с аргументами _Arguments.
         * Type - тип результата выполнения операции, определяемой типом _Operation с аргументами _Arguments.
         * В случае отсутствия операции, определяемой типом _Operation с аргументами _Arguments, тип Type является служебным типом Nonesuch.
         */

    template < typename _Default, template < typename ... > class _Operation, typename ... _Arguments >
    using DetectedOr = typename ::ScL::Meta::Detail::Detector< _Default, void, _Operation, _Arguments ... >;
        /*!<
         * Тип является вариантом типа Detector с вложеными типами Result и Type, представляющими результат операции, определяемой типом _Operation с аргументами _Arguments.
         * Result - логический тип, который отражает наличие или отсутствие операции, определяемой типом _Operation с аргументами _Arguments.
         * Type - тип результата выполнения операции, определяемой типом _Operation с аргументами _Arguments.
         * В случае отсутствия операции, определяемой типом _Operation с аргументами _Arguments, тип Type является указанным типом _Default.
         */

    template < template < typename ... > class _Operation, typename ... _Arguments >
    using DetectedType = typename Detected< _Operation, _Arguments ... >::Type;
        /*!<
         * Тип результата выполнения операции, определяемой типом _Operation с аргументами _Arguments.
         */

    template < template < typename ... > class _Operation, typename ... _Arguments >
    using DetectedResult = typename Detected< _Operation, _Arguments ... >::Result;
        /*!<
         * Логический тип, который отражает наличие или отсутствие операции, определяемой типом _Operation с аргументами _Arguments.
         */

    template < template < typename ... > class _Operation, typename ... _Arguments >
    using IsDetected = DetectedResult< _Operation, _Arguments ... >;
        /*!<
         * Синоним ResultOfDetected, который отражает наличие или отсутствие операции, определяемой типом _Operation с аргументами _Arguments.
         */
}}

namespace ScL { namespace Meta
{
    template < template < typename ... > class _Operation, typename ... _Arguments >
    /*inline*/ constexpr bool is_detected = IsDetected< _Operation, _Arguments ... >::value;

    template < typename _Expected, template < typename ... > class _Operation, typename ... _Arguments >
    /*inline*/ constexpr bool is_detected_exact = ::std::is_same< _Expected, DetectedType< _Operation, _Arguments ... > >::value;

    template < typename _Expected, template < typename ... > class _Operation, typename ... _Arguments >
    /*inline*/ constexpr bool is_detected_convertible = ::std::is_constructible< _Expected, DetectedType< _Operation, _Arguments ... > >::value;
}}

namespace ScL { namespace Meta
{
    template < template < typename ... > class _Operation, typename ... _Arguments >
    inline constexpr bool isDetected () { return DetectedResult< _Operation, _Arguments ... >::value; }
        /*!<
         * Возвращает логический результат наличия или отсутствия операции, определяемой типом _Operation с аргументами _Arguments.
         */

    template < typename _Expected, template < typename ... > class _Operation, typename ... _Arguments >
    inline constexpr bool isDetectedExact () { return ::std::is_same< _Expected, DetectedType< _Operation, _Arguments ... > >::value; }
        /*!<
         * Возвращает логический результат наличия или отсутствия операции, определяемой типом _Operation с аргументами _Arguments,
         * с точным соответствием возвращаемого значения типу _Expected.
         */

    template < typename _Expected, template < typename ... > class _Operation, typename ... _Arguments >
    inline constexpr bool isDetectedConvertible () { return ::std::is_constructible< _Expected, DetectedType< _Operation, _Arguments ... > >::value; }
        /*!<
         * Возвращает логический результат наличия или отсутствия операции, определяемой типом _Operation с аргументами _Arguments,
         * с конвертируемым типом возвращаемого значения к типу _Expected.
         */
}}

namespace ScL { namespace Meta
{
    template < template < typename ... > class _Operation, typename ... _Arguments >
    struct Detector
    {
        static constexpr bool isDetected () { return ::ScL::Meta::isDetected< _Operation, _Arguments ... >(); }
        template < typename _Expected > static constexpr bool isDetectedExact () { return ::ScL::Meta::isDetectedExact< _Expected, _Operation, _Arguments ... >(); }
        template < typename _Expected > static constexpr bool isDetectedConvertible () { return ::ScL::Meta::isDetectedConvertible< _Expected, _Operation, _Arguments ... >(); }
    };

    template < template < typename ... > class _Operation, typename _Result, typename ... _Arguments >
    struct Detector< _Operation, _Result( _Arguments ... ) >
    {
        static constexpr bool isDetected () { return ::ScL::Meta::isDetectedExact< _Result, _Operation, _Arguments ... >(); }
    };

    template < template < typename ... > class _Operation, typename _Type, typename _Result, typename ... _Arguments >
    struct Detector< _Operation, _Type, _Result( _Arguments ... ) >
    {
        static constexpr bool isDetected () { return ::ScL::Meta::isDetectedExact< _Result, _Operation, _Type, _Arguments ... >(); }
    };
}}

#endif
