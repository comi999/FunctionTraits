#include <iostream>
#include "FunctionTraits.hpp"

struct A { void foo() { }; };
void foo1() { };
auto l = [&]( int ) { return false; };

using M = decltype( &A::foo );
using S = decltype( foo1 );
using L = decltype( l );

static constexpr bool valA1 = FunctionTraits::FunctionInfo< M >::IsFunction;
static constexpr bool valA2 = FunctionTraits::FunctionInfo< M >::IsLambda;
static constexpr bool valA3 = FunctionTraits::FunctionInfo< M >::IsMember;
static constexpr bool valA4 = FunctionTraits::FunctionInfo< M >::IsStatic;

static constexpr bool valB1 = FunctionTraits::FunctionInfo< S >::IsFunction;
static constexpr bool valB2 = FunctionTraits::FunctionInfo< S >::IsLambda;
static constexpr bool valB3 = FunctionTraits::FunctionInfo< S >::IsMember;
static constexpr bool valB4 = FunctionTraits::FunctionInfo< S >::IsStatic;

static constexpr bool valC1 = FunctionTraits::FunctionInfo< L >::IsFunction;
static constexpr bool valC2 = FunctionTraits::FunctionInfo< L >::IsLambda;
static constexpr bool valC3 = FunctionTraits::FunctionInfo< L >::IsMember;
static constexpr bool valC4 = FunctionTraits::FunctionInfo< L >::IsStatic;

template < typename T, typename = FunctionTraits::EnableIfLambdaF< T > >
void func( T a_func )
{
}

template < typename T, typename = FunctionTraits::EnableIfMemberF< T > >
void func( T a_func )
{
}

template < typename T, typename = FunctionTraits::EnableIfStaticF< T > >
void func( T a_func )
{
}

template < typename T, typename = FunctionTraits::DisableIfFunction< T > >
void func( T a_func )
{
}

int main()
{
    func( &A::foo );
}