#include <ostream>
#include <cassert>
#include <cstring>	// for memcpy

#include "least-types.h"
using namespace least_types;


namespace bmp
{
	struct BitmapHeader;
	struct BITMAPINFOHEADER;
}

std::ostream& operator <<(std::ostream& p_os, bmp::BitmapHeader const& p);
std::ostream& operator <<(std::ostream& p_os, bmp::BITMAPINFOHEADER const& p);


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
		byte headerField[2];	// offset 0
		uint_least32_t fileSize;	// offset 2
		byte reserved0[2];	// offset 6
		byte reserved1[2];	// offset 8
		uint_least32_t dataOffset;	// offset 10

		friend std::ostream& operator <<(std::ostream& p_os, BitmapHeader const& p);
	};

	enum BitmapCompression
	{
		BI_RGB = 0,
		BI_RLE8,
		BI_RLE4,
		BI_BITFIELDS, //Also Huffman 1D compression for BITMAPCOREHEADER2
		BI_JPEG,      //Also RLE-24 compression for BITMAPCOREHEADER2
		BI_PNG,
	};

	struct BITMAPINFOHEADER
	{
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
