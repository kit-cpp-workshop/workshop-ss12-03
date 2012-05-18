#ifndef H_BMPTYPES
#define H_BMPTYPES



#include "least-types.h"

namespace bmp
{
	typedef unsigned char byte;

	typedef least_types :: least<  signed, 16>::type     int_least16_t;
	typedef least_types :: least<unsigned, 16>::type    uint_least16_t;
	typedef least_types :: least<  signed, 32>::type     int_least32_t;
	typedef least_types :: least<unsigned, 32>::type    uint_least32_t;
}




#endif // H_BMPTYPES