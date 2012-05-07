#include <cstdint>
#include <ostream>

// source: http://en.wikipedia.org/wiki/BMP_file_format
namespace bmp
{
	typedef uint8_t byte;

	struct BitmapHeader
	{
		byte headerField[2];
		uint32_t fileSize;
		byte reserved0[2];
		byte reserved1[2];
		uint32_t dataOffset;

		friend std::ostream& operator <<(std::ostream& p_os, BitmapHeader const& p)
		{
			p_os.write
			(
				reinterpret_cast<const char* const>(p.headerField),
				sizeof(p.headerField) * sizeof(p.headerField[0])
			);

			p_os.write( reinterpret_cast<const char* const>(&p.fileSize), sizeof(p.fileSize) );

			p_os.write
			(
				reinterpret_cast<const char* const>(p.reserved0),
				sizeof(p.reserved0) * sizeof(p.reserved0[0])
			);
			p_os.write
			(
				reinterpret_cast<const char* const>(p.reserved1),
				sizeof(p.reserved1) * sizeof(p.reserved1[0])
			);

			p_os.write( reinterpret_cast<const char* const>(&p.dataOffset), sizeof(p.dataOffset) );

			return p_os;
		}
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
		int32_t width;
		int32_t height;
		uint16_t bitsPP;
		BitmapCompression compressionType;
		uint32_t bmpDataSize;	// in [byte]
		int32_t hres;	// in [pixel/meter]
		int32_t vres;	// in [pixel/meter]
		uint32_t nColors;
		uint32_t nImportantColors;	// generally ignored

		friend std::ostream& operator <<(std::ostream& p_os, BITMAPINFOHEADER const& p)
		{
			static uint32_t const BITMAPINFOHEADER_SIZE = 40;
			p_os.write( reinterpret_cast<const char* const>(&BITMAPINFOHEADER_SIZE), sizeof(BITMAPINFOHEADER_SIZE) );

			p_os.write( reinterpret_cast<const char* const>(&p.width), sizeof(p.width) );
			p_os.write( reinterpret_cast<const char* const>(&p.height), sizeof(p.height) );

			static uint16_t const COLOR_PLANES = 1;
			p_os.write( reinterpret_cast<const char* const>(&COLOR_PLANES), sizeof(COLOR_PLANES) );

			p_os.write( reinterpret_cast<const char* const>(&p.bitsPP), sizeof(p.bitsPP) );

			p_os.write( reinterpret_cast<const char* const>(&p.compressionType), 4 );

			p_os.write( reinterpret_cast<const char* const>(&p.bmpDataSize), sizeof(p.bmpDataSize) );

			p_os.write( reinterpret_cast<const char* const>(&p.hres), sizeof(p.hres) );
			p_os.write( reinterpret_cast<const char* const>(&p.vres), sizeof(p.vres) );

			p_os.write( reinterpret_cast<const char* const>(&p.nColors), sizeof(p.nColors) );
			p_os.write( reinterpret_cast<const char* const>(&p.nImportantColors), sizeof(p.nImportantColors) );

			return p_os;
		}
	};
}
