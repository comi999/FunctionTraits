#include <tuple>
using namespace std;

namespace FunctionTraits
{
	template < typename T >
	struct FunctionInfo;

	template < typename R, typename... A >
	struct FunctionInfo< R( A... ) >
	{
		using Signature = R( A... );
		using Return = R;
		using Arguments = tuple< A... >;
		static constexpr bool IsStatic = true;
		static constexpr bool IsLambda = false;
		static constexpr bool IsMember = false;
		static constexpr bool IsFunction = IsStatic || IsLambda || IsMember;
	};

	template < typename O, typename R, typename... A >
	struct FunctionInfo< R( O::* )( A... ) >
		: FunctionInfo< R( A... ) >
	{
		static constexpr bool IsStatic = false;
		static constexpr bool IsLambda = false;
		static constexpr bool IsMember = true;
		static constexpr bool IsFunction = IsStatic || IsLambda || IsMember;
	};

	template < typename O, typename R, typename... A >
	struct FunctionInfo< R( O::* )( A... ) const >
		: FunctionInfo< R( A... ) >
	{
		static constexpr bool IsStatic = false;
		static constexpr bool IsLambda = false;
		static constexpr bool IsMember = true;
		static constexpr bool IsFunction = IsStatic || IsLambda || IsMember;
	};

	template < typename O, typename R, typename... A >
	struct FunctionInfo< R( O::* )( A... ) volatile >
		: FunctionInfo< R( A... ) >
	{
		static constexpr bool IsStatic = false;
		static constexpr bool IsLambda = false;
		static constexpr bool IsMember = true;
		static constexpr bool IsFunction = IsStatic || IsLambda || IsMember;
	};

	template < typename O, typename R, typename... A >
	struct FunctionInfo< R( O::* )( A... ) const volatile >
		: FunctionInfo< R( A... ) >
	{
		static constexpr bool IsStatic = false;
		static constexpr bool IsLambda = false;
		static constexpr bool IsMember = true;
		static constexpr bool IsFunction = IsStatic || IsLambda || IsMember;
	};

	template < typename R, typename... A >
	struct FunctionInfo< R( * )( A... ) >
		: FunctionInfo< R( A... ) >
	{
		static constexpr bool IsStatic = true;
		static constexpr bool IsLambda = false;
		static constexpr bool IsMember = false;
		static constexpr bool IsFunction = IsStatic || IsLambda || IsMember;
	};

	template < typename R, typename... A >
	struct FunctionInfo< R( & )( A... ) >
		: FunctionInfo< R( A... ) >
	{
		static constexpr bool IsStatic = true;
		static constexpr bool IsLambda = false;
		static constexpr bool IsMember = false;
		static constexpr bool IsFunction = IsStatic || IsLambda || IsMember;
	};

	template < typename T >
	struct FunctionInfo
	{
		template < typename U >
		struct HasInvocationOperator
		{
			template < typename V > static char test( decltype( &V::operator() ) );
			template < typename V > static long test( ... );
			static constexpr bool Value = sizeof( test< U >( 0 ) ) == sizeof( char );
		};

		template < typename U, bool Enable = HasInvocationOperator< U >::Value >
		struct GetInvocationSignature
		{
			using Type = void;
		};

		template < typename U >
		struct GetInvocationSignature< U, true >
		{
			using Type = decltype( &remove_reference< T >::type::operator() );
		};

		using Signature = typename GetInvocationSignature< T >::Type;
		using Return = typename FunctionInfo< Signature >::Return;
		using Arguments = typename FunctionInfo< Signature >::Arguments;
		static constexpr bool IsStatic = false;
		static constexpr bool IsLambda = HasInvocationOperator< T >::Value;
		static constexpr bool IsMember = false;
		static constexpr bool IsFunction = IsStatic || IsLambda || IsMember;
	};

	template <>
	struct FunctionInfo< void >
	{
		using Signature = void;
		using Return = void;
		using Arguments = void;
		static constexpr bool IsStatic = false;
		static constexpr bool IsLambda = false;
		static constexpr bool IsMember = false;
		static constexpr bool IsFunction = false;
	};

	template < typename T >
	using GetSignature = typename FunctionInfo< T >::Signature;

	template < typename T >
	using GetReturn = typename FunctionInfo< T >::Return;

	template < typename T >
	using GetArguments = typename FunctionInfo< T >::Arguments;

	template < typename T >
	using EnableIfLambdaF = enable_if_t< FunctionInfo< T >::IsLambda, void >;

	template < typename T >
	using DisableIfLambdaF = enable_if_t< !FunctionInfo< T >::IsLambda, void >;

	template < typename T >
	using EnableIfStaticF = enable_if_t< FunctionInfo< T >::IsStatic, void >;

	template < typename T >
	using DisableIfStaticF = enable_if_t< !FunctionInfo< T >::IsStatic, void >;

	template < typename T >
	using EnableIfMemberF = enable_if_t< FunctionInfo< T >::IsMember, void >;

	template < typename T >
	using DisableIfMemberF = enable_if_t< !FunctionInfo< T >::IsMember, void >;

	template < typename T >
	using EnableIfFunction = enable_if_t< FunctionInfo< T >::IsFunction, void >;

	template < typename T >
	using DisableIfFunction = enable_if_t< !FunctionInfo< T >::IsFunction, void >;
}