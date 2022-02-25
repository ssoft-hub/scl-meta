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

static_assert( Detector< FooFunctionUnstrictOperation, int >::isDetected(), "The foo(int) was defined but not detected!" );
static_assert( Detector< FooFunctionUnstrictOperation, int >::isDetectedExact< int >(), "The int foo(int) was defined but not detected!" );
static_assert( Detector< FooFunctionUnstrictOperation, char >::isDetectedConvertible< double >(), "The convertible int foo(int) was defined but not detected!" );

static_assert( Detector< FooFunctionStrictOperation, int >::isDetected(), "The foo(int) was defined but not detected!");
static_assert( Detector< FooFunctionStrictOperation, int >::isDetectedExact< int >(), "The int foo(int) was defined but not detected!");
static_assert( !Detector< FooFunctionStrictOperation, char >::isDetectedConvertible< double >(), "The convertible foo(char) was not defined but detected!");


static_assert( Detector< FooFunctionUnstrictOperation, int(int) >::isDetected(), "The foo(void) was defined but not detected!" );
static_assert( Detector< FooFunctionStrictOperation, int(int) >::isDetected(), "The foo(void) was defined but not detected!" );

//SCL_DOES_FUNCTION_EXIST( foo, Foo )
template < typename ... _Arguments >
inline static constexpr bool doesFooFunctionExist() { return ::ScL::Meta::Detector< FooFunctionStrictOperation, _Arguments ... >::isDetected(); }

static_assert( doesFooFunctionExist<>(), "The foo() was defined but not detected!" );
static_assert( doesFooFunctionExist< void() >(), "The foo() was defined but not detected!" );
static_assert( doesFooFunctionExist< int >(), "The foo(int) was defined but not detected!" );
static_assert( doesFooFunctionExist< int(int) >(), "The foo(int) was defined but not detected!" );
static_assert( doesFooFunctionExist< double >(), "The foo(double) was defined but not detected!" );
static_assert( doesFooFunctionExist< double(double) >(), "The foo(double) was defined but not detected!" );
static_assert( doesFooFunctionExist< int, double >(), "The foo(double) was defined but not detected!" );
static_assert( doesFooFunctionExist< void(int, double) >(), "The foo(double) was defined but not detected!" );
static_assert( !doesFooFunctionExist< double, int >(), "The foo(double) was defined but not detected!" );
static_assert( !doesFooFunctionExist< void(double, int) >(), "The foo(double) was defined but not detected!" );
static_assert( !doesFooFunctionExist< char >(), "The foo(char) was not defined but detected!" );
static_assert( !doesFooFunctionExist< int(char) >(), "The foo(char) was not defined but detected!" );

////////////////////////////////////////////////////////////////////////////////
/// MEMBER METHOD DETECTION TEST

// Define some kinds of foo member

//SCL_DOES_COMPATIBLE_METHOD_EXIST( foo, Foo )
//SCL_DOES_STATIC_METHOD_EXIST( foo, Foo )
//SCL_DOES_METHOD_EXIST( foo, Foo )



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

static_assert( Detector< FooMethodStrictOperation, A const, int >::isDetected(), "The member int A::foo(int) const was declared but not detected!" );
static_assert( Detector< FooMethodStrictOperation, A const, int >::isDetectedExact< int >(), "The member int A::foo(int) const was declared but not detected!" );
static_assert( Detector< FooMethodStrictOperation, A const, int >::isDetectedConvertible< double >(), "The convertible member int A::foo(int) const was declared but not detected!" );
static_assert( Detector< FooMethodStrictOperation, A const, int(int) >::isDetected(), "The member int A::foo(int) const was declared but not detected!" );
static_assert( !Detector< FooMethodStrictOperation, A const, void(int) >::isDetected(), "The member int A::foo(int) const was declared but not detected!" );

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

C operator - ( const C & left, const C & right );   // global binary



// Any member
    template < typename _Type, typename ... _Arguments >
    using OperatorPlusPlusUnstrictOperation = decltype( ::std::declval< _Type >().operator ++ ( ::std::declval< _Arguments >() ... ) );

    template < typename _Type, typename ... _Arguments >
    using OperatorPlusPlusStrictOperation = decltype( (::std::declval< _Type >() .* ::std::integral_constant< ::ScL::SimilarMethod< _Type, OperatorPlusPlusUnstrictOperation< _Type, _Arguments ... >( _Arguments ... ) >
        , &::std::decay_t< _Type >::operator ++ >::value)( ::std::declval< _Arguments >() ... ) );

// Any global
//    template < typename _Left, typename _Right, typename = ::std::enable_if_t < ::std::is_pod< _Left >::value && ::std::is_pod< _Right >::value > >
//    auto baseOperatorMinus ( _Left && left, _Right && right ) -> decltype( ::std::declval< _Left && > - ::std::declval< _Right && > );

//    template < typename ... _Arguments >
//    using OperatorMinusUnstrictOperation = decltype( operator - ( ::std::declval< _Arguments >() ... ) );

    template < typename _Left, typename _Right >
    using OperatorMinusUnstrictOperation = decltype( ::std::declval< _Left >() - ::std::declval< _Right >() );

    template < typename _Left, typename _Right >
    using MemberMinusStrictOperation = decltype( (::std::declval< _Left >() .* ::std::integral_constant< ::ScL::SimilarMethod< _Left, OperatorMinusUnstrictOperation< _Left, _Right >( _Right ) >
        , &::std::decay_t< _Left >::operator - >::value)( ::std::declval< _Right >() ) );

    template < typename _Left, typename _Right >
    using GlobalMinusStrictOperation = decltype( (::std::integral_constant< OperatorMinusUnstrictOperation< _Left, _Right >(*)( _Left, _Right ), &operator - >::value)( ::std::declval< _Left >(), ::std::declval< _Right >() ) );

//    template < typename _Type, typename ... >
//    using PrefixPlusPlusUnstrictOperation = decltype( ++ ::std::declval< _Type >() );

static_assert( isDetected< PrefixPlusPlusUnstrictOperation, C >(), "" );
static_assert( isDetected< PrefixPlusPlusMemberStrictOperation, C const >(), "" );
static_assert( !::ScL::Meta::isDetected< PrefixPlusPlusUnstrictOperation, int >(), "" );

static_assert( isDetected< SubtractionUnstrictOperation, C, int >(), "" );
static_assert( isDetected< SubtractionMemberStrictOperation, C const, int >(), "" );
//static_assert( isDetected< SubtractionGlobalStrictOperation, C const &, C const & >(), "" );

// TODO: trivial types
static_assert( isDetected< OperatorMinusUnstrictOperation, int, int >(), "" );
//static_assert( isDetected< GlobalMinusStrictOperation, int, int >(), "" );



//static_assert( doesStaticFooMethodExist< B, void() >(), "" );
//static_assert( doesStaticFooMethodExist< B >(), "The member void B::foo() const & was declared but not detected!" );
//static_assert( doesStaticFooMethodExist< B, void() >(), "The member void B::foo() const & was declared but not detected!" );

//// Дописать специализацию FooDetector
//static_assert( doesFooMethodExist< B const &, int >(), "The member void B::foo() const & was not declared but detected!" );
//static_assert( !doesFooMethodExist< B const &, int(int) >(), "The member void B::foo() const & was not declared but detected!" );

//static_assert( doesFooMethodExist< B const, void(int) >(), "The member void B::foo() const & was not declared but detected!" );
//static_assert( doesFooMethodExist< B const &, void(int) >(), "The member void B::foo() const & was not declared but detected!" );
//static_assert( doesFooMethodExist< B const &&, void(int) >(), "The member void B::foo() const & was not declared but detected!" );

//static_assert( !doesFooMethodExistExact< B const, void(int) >(), "The member void B::foo() const & was not declared but detected!" );
//static_assert( doesFooMethodExistExact< B const &, void(int) >(), "The member void B::foo() const & was not declared but detected!" );
//static_assert( doesFooMethodExistExact< B const &&, void(int) >(), "The member void B::foo() const & was not declared but detected!" );

//static_assert( isDetected< FooMethodUnstrictOperation, B >(), "" );

int main ( int, char ** )
{
//    using Stream = int;
//    using Value = int;


//    static_assert( !doesFooMethodExist< B >(), "" );
//    static_assert( doesFooMethodExist< C, int >(), "" );

//    static_assert( doesFooMethodExist< A, void(void) >(), "" );


//    if ( isDetected< ValueFunction >() )
//        /*true*/;

//    if ( isDetected< LeftShiftOperator, Stream, Value >() )
//        /*true*/;

//    if ( isDetected< ValueFunction, int >() )
//        /*false*/;

////    if ( isDetected< LeftShiftOperator< Stream, Value > >() )
////        /*true*/;

    return 0;
}
