#ifndef H_LEAST_TYPES
#define H_LEAST_TYPES




#include <climits>


namespace least_types
{
	// If your compiler does not support `unsigned long long`, use `unsigned long` instead
	// AND use `1ul` instead of `1ull`
	typedef unsigned long long largest_int;
	#define LEAST_TYPES_LARGEST_UNITY 1ull


	template < largest_int _p0, largest_int _p1 >
	struct smallEq
	{
		enum { value = _p0 <= _p1 };
	};


	template < typename _then, typename _else, bool _b >
	struct ifThenElse
	{};
		template < typename _then, typename _else >
		struct ifThenElse < _then, _else, true > { typedef _then value; };

		template < typename _then, typename _else >
		struct ifThenElse < _then, _else, false > { typedef _else value; };


#define LEAST_TYPES_ASCEND \
	template < largest_int _num > \
	struct least_cmp \
	{ \
		typedef typename ifThenElse < type_max < own >, typename bigger::least_cmp<_num>::type, smallEq < _num, MAX > :: value > :: value type; \
	}

#define LEAST_TYPES_TYPE(name, max_value, bigger_t) \
	template <> \
	struct type_max < name > \
	{ \
		typedef name own; \
		enum { MAX = max_value }; \
		typedef type_max < bigger_t > bigger; \
		LEAST_TYPES_ASCEND; \
	}

	class no_bigger_available
	{
		virtual ~no_bigger_available(){}
		virtual void error() = 0;
	};

	template < typename _T >
	struct type_max
	{};
		template <>
		struct type_max < no_bigger_available >
		{
			template < largest_int _num >
			struct least_cmp
			{
				typedef no_bigger_available type;
			};
		};

		LEAST_TYPES_TYPE(long int, LONG_MAX, no_bigger_available);
		LEAST_TYPES_TYPE(int, INT_MAX, long int);
		LEAST_TYPES_TYPE(short int, SHRT_MAX, int);

		LEAST_TYPES_TYPE(unsigned long int, ULONG_MAX, no_bigger_available);
		LEAST_TYPES_TYPE(unsigned int, UINT_MAX, unsigned long int);
		LEAST_TYPES_TYPE(unsigned short int, USHRT_MAX, unsigned int);


	template < typename _Signed, largest_int _bits >
	struct least
	{};
		template < largest_int _bits >
		struct least < signed, _bits >
		{
			// NOTE: _bits-2
			typedef typename type_max <   signed short int > :: template least_cmp < ((((LEAST_TYPES_LARGEST_UNITY << (_bits-2)) - 1) << 1) + 1) > :: type :: own
			        type;
		};

		template < largest_int _bits >
		struct least < unsigned, _bits >
		{
			// NOTE: _bits-1
			typedef typename type_max < unsigned short int > :: template least_cmp < ((((LEAST_TYPES_LARGEST_UNITY << (_bits-1)) - 1) << 1) + 1) > :: type :: own
			        type;
		};
}




#endif // H_LEAST_TYPES
