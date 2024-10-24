#pragma once
#ifndef SCL_META_COUNTER_H
#define SCL_META_COUNTER_H

#include <cstdint>
#include <type_traits>

// https://stackoverflow.com/a/6174263/1190123

namespace ScL { namespace Meta
{
    template< ::std::uint_fast32_t _n >
    struct CounterValue : ::std::integral_constant< ::std::uint_fast32_t, _n > {};
}}

namespace ScL { namespace Meta
{
    template< typename Tag_, ::std::uint_fast32_t _rank, ::std::uint_fast32_t _acc >
    constexpr ::ScL::Meta::CounterValue< _acc >
    crumb( Tag_,
        ::ScL::Meta::CounterValue< _rank >,
        ::ScL::Meta::CounterValue< _acc > )
    { return {}; }
}}

#define SCL_META_COUNTER_FORWARD( ... )  __VA_ARGS__

#define SCL_META_COUNTER_CRUMB( Tag, rank, acc ) \
    ::ScL::Meta::crumb( Tag{}, ::ScL::Meta::CounterValue< rank >(), ::ScL::Meta::CounterValue< acc >() ) \

#define SCL_META_COUNTER_VALUE( Tag ) \
    SCL_META_COUNTER_CRUMB( SCL_META_COUNTER_FORWARD(Tag), 1ul << 0, \
    SCL_META_COUNTER_CRUMB( SCL_META_COUNTER_FORWARD(Tag), 1ul << 1, \
    SCL_META_COUNTER_CRUMB( SCL_META_COUNTER_FORWARD(Tag), 1ul << 2, \
    SCL_META_COUNTER_CRUMB( SCL_META_COUNTER_FORWARD(Tag), 1ul << 3, \
    SCL_META_COUNTER_CRUMB( SCL_META_COUNTER_FORWARD(Tag), 1ul << 4, \
    SCL_META_COUNTER_CRUMB( SCL_META_COUNTER_FORWARD(Tag), 1ul << 5, \
    SCL_META_COUNTER_CRUMB( SCL_META_COUNTER_FORWARD(Tag), 1ul << 6, \
    SCL_META_COUNTER_CRUMB( SCL_META_COUNTER_FORWARD(Tag), 1ul << 7, \
    SCL_META_COUNTER_CRUMB( SCL_META_COUNTER_FORWARD(Tag), 1ul << 8, \
    SCL_META_COUNTER_CRUMB( SCL_META_COUNTER_FORWARD(Tag), 1ul << 9, \
    SCL_META_COUNTER_CRUMB( SCL_META_COUNTER_FORWARD(Tag), 1ul << 10, \
    SCL_META_COUNTER_CRUMB( SCL_META_COUNTER_FORWARD(Tag), 1ul << 11, \
    SCL_META_COUNTER_CRUMB( SCL_META_COUNTER_FORWARD(Tag), 1ul << 12, \
    SCL_META_COUNTER_CRUMB( SCL_META_COUNTER_FORWARD(Tag), 1ul << 13, \
    SCL_META_COUNTER_CRUMB( SCL_META_COUNTER_FORWARD(Tag), 1ul << 14, \
    SCL_META_COUNTER_CRUMB( SCL_META_COUNTER_FORWARD(Tag), 1ul << 15, \
    SCL_META_COUNTER_CRUMB( SCL_META_COUNTER_FORWARD(Tag), 1ul << 16, \
    SCL_META_COUNTER_CRUMB( SCL_META_COUNTER_FORWARD(Tag), 1ul << 17, \
    SCL_META_COUNTER_CRUMB( SCL_META_COUNTER_FORWARD(Tag), 1ul << 18, \
    SCL_META_COUNTER_CRUMB( SCL_META_COUNTER_FORWARD(Tag), 1ul << 19, \
    SCL_META_COUNTER_CRUMB( SCL_META_COUNTER_FORWARD(Tag), 1ul << 20, \
    SCL_META_COUNTER_CRUMB( SCL_META_COUNTER_FORWARD(Tag), 1ul << 21, \
    SCL_META_COUNTER_CRUMB( SCL_META_COUNTER_FORWARD(Tag), 1ul << 22, \
    SCL_META_COUNTER_CRUMB( SCL_META_COUNTER_FORWARD(Tag), 1ul << 23, \
    SCL_META_COUNTER_CRUMB( SCL_META_COUNTER_FORWARD(Tag), 1ul << 24, \
    SCL_META_COUNTER_CRUMB( SCL_META_COUNTER_FORWARD(Tag), 1ul << 25, \
    SCL_META_COUNTER_CRUMB( SCL_META_COUNTER_FORWARD(Tag), 1ul << 26, \
    SCL_META_COUNTER_CRUMB( SCL_META_COUNTER_FORWARD(Tag), 1ul << 27, \
    SCL_META_COUNTER_CRUMB( SCL_META_COUNTER_FORWARD(Tag), 1ul << 28, \
    SCL_META_COUNTER_CRUMB( SCL_META_COUNTER_FORWARD(Tag), 1ul << 29, \
    SCL_META_COUNTER_CRUMB( SCL_META_COUNTER_FORWARD(Tag), 1ul << 30, \
    SCL_META_COUNTER_CRUMB( SCL_META_COUNTER_FORWARD(Tag), 1ul << 31, \
    0 ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) \

#define SCL_META_COUNTER_NEXT( Tag ) \
    namespace ScL { namespace Meta \
    { \
        constexpr ::ScL::Meta::CounterValue< SCL_META_COUNTER_VALUE( SCL_META_COUNTER_FORWARD(Tag) ) + 1 > \
        crumb( Tag, \
            ::ScL::Meta::CounterValue< ( SCL_META_COUNTER_VALUE( SCL_META_COUNTER_FORWARD(Tag) ) + 1 ) & ~SCL_META_COUNTER_VALUE( SCL_META_COUNTER_FORWARD(Tag) ) >, \
            ::ScL::Meta::CounterValue< ( SCL_META_COUNTER_VALUE( SCL_META_COUNTER_FORWARD(Tag) ) + 1 ) & SCL_META_COUNTER_VALUE( SCL_META_COUNTER_FORWARD(Tag) ) > ) \
        { return {}; } \
    }} \

// http://b.atch.se/posts/non-constant-constant-expressions/
// http://b.atch.se/posts/constexpr-counter/#prereq-adl
// https://stackoverflow.com/questions/44267673/is-stateful-metaprogramming-ill-formed-yet
// http://www.open-std.org/jtc1/sc22/wg21/docs/cwg_active.html#2118

//namespace ScL::Meta
//{
//    template < typename _Tag >
//    class Counter
//    {
//        using Value = int;

//        template < Value _n >
//        struct Index
//        {
//            friend constexpr Value adlValue ( Index< _n > );
//        };

//        template < Value _n >
//        struct Writer
//        {
//            friend constexpr Value adlValue ( Index< _n > ) { return _n; }
//            static constexpr Value value = _n;
//        };

//        template < Value _n >
//        static constexpr Value increment ( float, Index< _n > )
//        { return _n; }

//        template < Value _n, Value = adlValue( Index< _n >{} ) >
//        static constexpr Value increment ( Value, Index< _n >, Value v = increment( 0, Index< _n + 1 >{} ) )
//        { return v; }

//    public:
//        template < Value _n = 0 >
//        static constexpr Value next ( Value v = value_of< Writer< increment( 0, Index< 0 >{} ) + _n > > )
//        { return v + 1; }

//        template < Value _n = 0 >
//        static constexpr Value value ( Value v = value_of< Writer< increment( 0, Index< 0 >{} ) + _n - 1 > > )
//        { return v + 1; }
//    };
//}

#endif
