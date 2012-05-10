#include <ostream>
#include <cassert>
#include <cstring>	// for memcpy
#include <cstddef>

#include "least-types.h"
using namespace least_types;


// source: http://en.wikipedia.org/wiki/BMP_file_format
namespace bmp
{
	typedef char byte;
	typedef least<  signed, 16>::type     int_least16_t;
	typedef least<unsigned, 16>::type    uint_least16_t;
	typedef least<  signed, 32>::type     int_least32_t;
	typedef least<unsigned, 32>::type    uint_least32_t;


	bool isBigEndian();

	void convert2BigEndian(byte* dst, std::size_t dstCount,
	                       byte const* src, std::size_t srcCount);

	struct BitmapHeader
	{
		static std::size_t const SIZE = 14;


		byte headerField[2];
		uint_least32_t fileSize;
		byte reserved0[2];
		byte reserved1[2];
		uint_least32_t dataOffset;


		friend std::ostream& operator <<(std::ostream& p_os, BitmapHeader const& p);
	};


	struct BITMAPINFOHEADER
	{
		static std::size_t const SIZE = 40;


		enum BitmapCompression
		{
			BI_RGB = 0,
			BI_RLE8,
			BI_RLE4,
			BI_BITFIELDS, //Also Huffman 1D compression for BITMAPCOREHEADER2
			BI_JPEG,      //Also RLE-24 compression for BITMAPCOREHEADER2
			BI_PNG,
		};


		int_least32_t width;
		int_least32_t height;
		uint_least16_t bitsPP;
		BitmapCompression compressionType;
		uint_least32_t bmpDataSize;	// in [byte]
		int_least32_t hres;	// in [pixel/meter]
		int_least32_t vres;	// in [pixel/meter]
		uint_least32_t nColors;
		uint_least32_t nImportantColors;	// generally ignored


		friend std::ostream& operator <<(std::ostream& p_os, BITMAPINFOHEADER const& p);
	};
}
