#include <iostream>
#include "FunctionTraits.hpp"

struct A
{
	bool foo3( int, double, float )
	{
		return false;
	}
};
int foo4( double )
{
	return 10;
}
auto l = [&]( float )
{
	return "";
};

using M = decltype( &A::foo3 );
using S = decltype( foo4 );
using L = decltype( l );
using O = int;

static constexpr bool valA1 = FunctionTraits::Info< M >::IsFunction;
static constexpr bool valA2 = FunctionTraits::Info< M >::IsLambda;
static constexpr bool valA3 = FunctionTraits::Info< M >::IsMember;
static constexpr bool valA4 = FunctionTraits::Info< M >::IsStatic;
                                            
static constexpr bool valB1 = FunctionTraits::Info< S >::IsFunction;
static constexpr bool valB2 = FunctionTraits::Info< S >::IsLambda;
static constexpr bool valB3 = FunctionTraits::Info< S >::IsMember;
static constexpr bool valB4 = FunctionTraits::Info< S >::IsStatic;
                                            
static constexpr bool valC1 = FunctionTraits::Info< L >::IsFunction;
static constexpr bool valC2 = FunctionTraits::Info< L >::IsLambda;
static constexpr bool valC3 = FunctionTraits::Info< L >::IsMember;
static constexpr bool valC4 = FunctionTraits::Info< L >::IsStatic;

static constexpr bool valD1 = FunctionTraits::Info< O >::IsFunction;
static constexpr bool valD2 = FunctionTraits::Info< O >::IsLambda;
static constexpr bool valD3 = FunctionTraits::Info< O >::IsMember;
static constexpr bool valD4 = FunctionTraits::Info< O >::IsStatic;

template < typename T >
FunctionTraits::EnableIfStatic< T, void > func( T t )
{
	std::cout << "THIS IS A STATIC FUNCTION" << std::endl;
}

template < typename T >
FunctionTraits::EnableIfMember< T, void > func( T t )
{
	std::cout << "THIS IS A MEMBER FUNCTION" << std::endl;
}

template < typename T >
FunctionTraits::EnableIfLambda< T, void > func( T t )
{
	std::cout << "THIS IS A LAMBDA FUNCTION" << std::endl;
}

template < typename T >
FunctionTraits::DisableIfFunction< T, void > func( T t )
{
	std::cout << "THIS IS NOT A FUNCTION" << std::endl;
}

int main()
{
	A a;

	func( foo4 );
	func( &A::foo3 );
	func( l );
    func( a );
}