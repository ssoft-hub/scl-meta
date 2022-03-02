#include <ScL/Meta.h>

using namespace ::ScL::Meta;

////////////////////////////////////////////////////////////////////////////////
/// FUNCTION DETECTION TEST

// Define some kinds of foo function
void foo () {}
int foo ( int ) { return {}; }
double foo ( double ) { return {}; }
void foo ( int, double ) {}

// Define archetypal type for operation

template < typename ... _Arguments >
using FooFunctionUnstrictOperation = decltype( foo( ::std::declval< _Arguments >() ... ) );

template < typename ... _Arguments >
using FooFunctionStrictOperation = decltype( ::std::integral_constant< FooFunctionUnstrictOperation< _Arguments ... >(*)( _Arguments ... ), (&foo) >::value( ::std::declval< _Arguments >() ... ) );

// Test
static_assert( isDetected< FooFunctionUnstrictOperation >(), "The foo() was defined but not detected!" );
static_assert( isDetected< FooFunctionUnstrictOperation, int >(), "The foo(int) was defined but not detected!" );
static_assert( isDetected< FooFunctionUnstrictOperation, double >(), "The foo(double) was defined but not detected!" );
static_assert( isDetected< FooFunctionUnstrictOperation, char >(), "The convenient foo(int) was defined but not detected!" );
static_assert( isDetected< FooFunctionUnstrictOperation, int, double >(), "The foo(int,double) was defined but not detected!" );
static_assert( isDetected< FooFunctionUnstrictOperation, int, int >(), "The convenient foo(int,double) was defined but not detected!" );
static_assert( isDetected< FooFunctionUnstrictOperation, double, double >(), "The convenient foo(int,double) was defined but not detected!" );

static_assert( isDetected< FooFunctionStrictOperation >(), "The foo() was defined but not detected!" );
static_assert( isDetected< FooFunctionStrictOperation, int >(), "The foo(int) was defined but not detected!" );
static_assert( isDetected< FooFunctionStrictOperation, double >(), "The foo(double) was defined but not detected!" );
static_assert( !isDetected< FooFunctionStrictOperation, char >(), "The foo(char) was not defined but detected!" );
static_assert( isDetected< FooFunctionStrictOperation, int, double >(), "The foo(int,double) was defined but not detected!" );
static_assert( !isDetected< FooFunctionStrictOperation, int, int >(), "The foo(int,int) was not defined but detected!" );
static_assert( !isDetected< FooFunctionStrictOperation, double, double >(), "The foo(double,double) was not defined but detected!" );

static_assert( isDetectedExact< void, FooFunctionUnstrictOperation >(), "The void foo() was defined but not detected!" );
static_assert( !isDetectedExact< void, FooFunctionUnstrictOperation, int >(), "The void foo(int) was not defined but detected!" );
static_assert( isDetectedExact< int, FooFunctionUnstrictOperation, int >(), "The int foo(int) was defined but not detected!" );
static_assert( !isDetectedExact< double, FooFunctionUnstrictOperation, int >(), "The double foo(int) was not defined but detected!" );
static_assert( isDetectedExact< int, FooFunctionUnstrictOperation, char >(), "The convertible int foo(int) was defined but not detected!" );
static_assert( isDetectedConvertible< double, FooFunctionUnstrictOperation, int >(), "The convertible int foo(int) was defined but not detected!" );

static_assert( isDetectedExact< void, FooFunctionStrictOperation >(), "The void foo() was defined but not detected!" );
static_assert( !isDetectedExact< void, FooFunctionStrictOperation, int >(), "The void foo(int) was not defined but detected!" );
static_assert( isDetectedExact< int, FooFunctionStrictOperation, int >(), "The int foo(int) was defined but not detected!" );
static_assert( !isDetectedExact< double, FooFunctionStrictOperation, int >(), "The double foo(int) was not defined but detected!" );
static_assert( !isDetectedExact< int, FooFunctionStrictOperation, char >(), "The int foo(char) was not defined but detected!" );
static_assert( isDetectedConvertible< double, FooFunctionStrictOperation, int >(), "The convertible int foo(int) was defined but not detected!" );

// Detector

static_assert( isDetected< FooFunctionUnstrictOperation, int >(), "The foo(int) was defined but not detected!" );
static_assert( isDetectedExact< int, FooFunctionUnstrictOperation, int >(), "The int foo(int) was defined but not detected!" );
static_assert( isDetectedConvertible< double, FooFunctionUnstrictOperation, char >(), "The convertible int foo(int) was defined but not detected!" );

static_assert( isDetected< FooFunctionStrictOperation, int >(), "The foo(int) was defined but not detected!");
static_assert( isDetectedExact< int, FooFunctionStrictOperation, int >(), "The int foo(int) was defined but not detected!");
static_assert( !isDetectedConvertible< double, FooFunctionStrictOperation, char >(), "The convertible foo(char) was not defined but detected!");

template < typename ... _Arguments >
inline static constexpr bool doesFooFunctionExist() { return ::ScL::Meta::isDetected< FooFunctionStrictOperation, _Arguments ... >(); }

static_assert( doesFooFunctionExist<>(), "The foo() was defined but not detected!" );
static_assert( doesFooFunctionExist< int >(), "The foo(int) was defined but not detected!" );
static_assert( doesFooFunctionExist< double >(), "The foo(double) was defined but not detected!" );
static_assert( doesFooFunctionExist< int, double >(), "The foo(double) was defined but not detected!" );
static_assert( !doesFooFunctionExist< double, int >(), "The foo(double) was defined but not detected!" );
static_assert( !doesFooFunctionExist< void(double, int) >(), "The foo(double) was defined but not detected!" );
static_assert( !doesFooFunctionExist< char >(), "The foo(char) was not defined but detected!" );
static_assert( !doesFooFunctionExist< int(char) >(), "The foo(char) was not defined but detected!" );

////////////////////////////////////////////////////////////////////////////////
/// MEMBER METHOD DETECTION TEST

// Define some kinds of foo member
template < typename _Type, typename ... _Arguments >
using FooUnstrictMemberOperation = decltype( ::std::declval< _Type >(). foo ( ::std::declval< _Arguments >() ... ) );

template < typename _Type, typename ... _Arguments >
using FooStaticMethodStrictOperation = decltype( ::std::integral_constant< FooUnstrictMemberOperation< _Type, _Arguments ... >(*)( _Arguments ... ), &::std::decay_t< _Type >::foo >::value( ::std::declval< _Arguments >() ... ) );

template < typename _Type, typename ... _Arguments >
using FooMethodStrictOperation = decltype( (::std::declval< _Type >() .* ::std::integral_constant< ::ScL::SimilarMethod< _Type, FooUnstrictMemberOperation< _Type, _Arguments ... >( _Arguments ... ) >, &::std::decay_t< _Type >::foo >::value)( ::std::declval< _Arguments >() ... ) );

////////////////////////////////////////////////////////////////////////////////
///

struct A
{
    void foo ();
    int foo ( int ) const;
};

static_assert( isDetected< FooUnstrictMemberOperation, A >(), "The member A::foo() was declared but not detected!" );
static_assert( !isDetected< FooUnstrictMemberOperation, A const >(), "The member A::foo() const was not declared but detected!" );
static_assert( isDetected< FooUnstrictMemberOperation, A, int >(), "The member A::foo(int) const was declared but not detected!" );
static_assert( isDetected< FooUnstrictMemberOperation, A, double >(), "The convenient member A::foo(int) const was declared but not detected!" );

static_assert( isDetectedExact< void, FooUnstrictMemberOperation, A >(), "The member void A::foo() was declared but not detected!" );
static_assert( isDetectedExact< int, FooUnstrictMemberOperation, A, int >(), "The member int A::foo(int) const was declared but not detected!" );
static_assert( isDetectedExact< int, FooUnstrictMemberOperation, A, double >(), "The convenient member int A::foo(int) const was declared but not detected!" );
static_assert( !isDetectedExact< double, FooUnstrictMemberOperation, A, double >(), "The convenient member double A::foo(double) was not declared but detected!" );
static_assert( isDetectedConvertible< double, FooUnstrictMemberOperation, A, double >(), "The convertible member int A::foo(int) const was declared but not detected!" );

static_assert( isDetected< FooMethodStrictOperation, A >(), "The member A::foo() was declared but not detected!" );
static_assert( !isDetected< FooMethodStrictOperation, A, int >(), "The member A::foo(int) was not declared but detected!" );
static_assert( isDetected< FooMethodStrictOperation, A const, int >(), "The member A::foo(int) const was declared but not detected!" );
static_assert( !isDetected< FooMethodStrictOperation, A const, double >(), "The member A::foo(double) const was not declared but detected!" );

static_assert( isDetectedExact< void, FooMethodStrictOperation, A >(), "The member void A::foo() was declared but not detected!" );
static_assert( isDetectedExact< int, FooMethodStrictOperation, A const, int >(), "The member int A::foo(int) const was declared but not detected!" );
static_assert( !isDetectedExact< double, FooMethodStrictOperation, A, double >(), "The convenient member double A::foo(double) was not declared but detected!" );
static_assert( isDetectedConvertible< double, FooMethodStrictOperation, A const, int >(), "The convertible member int A::foo(int) const was declared but not detected!" );

static_assert( isDetected< FooMethodStrictOperation, A const, int >(), "The member int A::foo(int) const was declared but not detected!" );
static_assert( isDetectedExact< int, FooMethodStrictOperation, A const, int >(), "The member int A::foo(int) const was declared but not detected!" );
static_assert( isDetectedConvertible< double, FooMethodStrictOperation, A const, int >(), "The convertible member int A::foo(int) const was declared but not detected!" );

struct B
{
    static void foo();
    void foo( int ) const &;
    void foo ( int ) const &&;
};

static_assert( isDetected< FooStaticMethodStrictOperation, B >(), "The static member void B::foo() was declared but not detected!" );
static_assert( !isDetected< FooMethodStrictOperation, B const, int >(), "The member void B::foo(int) const was not declared but detected!" );
static_assert( isDetected< FooMethodStrictOperation, B const &, int >(), "The member void B::foo() const & was declared but not detected!" );
static_assert( isDetected< FooMethodStrictOperation, B const &&, int >(), "The member void B::foo() const && was declared but not detected!" );


struct C
{
    void foo ();

    int operator ++ ();         // unary postfix
    int operator ++ () const;   // unary prefix
    int operator ++ ( int );    // unary postfix
    C operator - ( int ) const;       // binary
};

C operator - (const C& left, const C& right);   // global binary

// Any member
    template < typename _Type >
    using TestPlusPlusUnstrictOperation = decltype( ++ ::std::declval< _Type >() );

    template < typename _Type >
    using TestPlusPlusStrictOperation = decltype( (::std::declval< _Type >() .* ::std::integral_constant< ::ScL::SimilarMethod< _Type, TestPlusPlusUnstrictOperation< _Type >() >, &::std::decay_t< _Type >::operator ++ >::value)() );

// Any global
    template < typename _Left, typename _Right >
    using TestSubtractionUnstrictOperation = decltype( ::std::declval< _Left >() - ::std::declval< _Right >() );

    template < typename _Left, typename _Right >
    using TestSubtractionMemberStrictOperation = decltype( (::std::declval< _Left >() .* ::std::integral_constant< ::ScL::SimilarMethod< _Left, TestSubtractionUnstrictOperation< _Left, _Right >( _Right ) >
        , &::std::decay_t< _Left >::operator - >::value)( ::std::declval< _Right >() ) );

    template < typename _Left, typename _Right >
    using TestSubtractionGlobalStrictOperation = decltype( (::std::integral_constant< TestSubtractionUnstrictOperation< _Left, _Right >(*)( _Left, _Right ), (&operator -) >::value)( ::std::declval< _Left >(), ::std::declval< _Right >() ) );

static_assert( isDetected< TestPlusPlusUnstrictOperation, C >(), "The member C::operator ++ () was declared but not detected!" );
static_assert( isDetected< TestPlusPlusStrictOperation, C const >(), "The member C::operator ++ () const was declared but not detected!" );
static_assert( isDetected< TestPlusPlusUnstrictOperation, int & >(), "The fundamental int::operator ++ () & exists but not detected!" );
static_assert( !isDetected< TestPlusPlusUnstrictOperation, int >(), "The fundamental int::operator ++ () not exists but detected!");

static_assert( isDetected< TestSubtractionUnstrictOperation, C, int >(), "The member C::operator - (int) const was declared but not detected!" );
static_assert( isDetected< TestSubtractionMemberStrictOperation, C const, int >(), "The member C::operator - (int) const was declared but not detected!" );
static_assert( isDetected< TestSubtractionGlobalStrictOperation, C const &, C const & >(), "The global operator - (C const &, C const &) was declared but not detected!" );

// trivial types
static_assert( isDetected< TestSubtractionUnstrictOperation, int, int >(), "The fundamental operator - (int, int) exists but not detected!" );
static_assert( !isDetected< TestSubtractionGlobalStrictOperation, int, int >(), "The fundamental operator - (int, int) has no strict detection!" );

int main ( int, char ** )
{
    return 0;
}
