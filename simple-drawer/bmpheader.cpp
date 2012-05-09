#include <algorithm>	// for min, max
#include "bmpheader.h"


namespace bmp
{
	bool isBigEndian()
	{
		assert(1 == sizeof(char));

		int_least16_t value = 1;
		unsigned char* firstByte = reinterpret_cast<unsigned char*>( &value );
		unsigned char test = 1;

		bool ret = (*firstByte == test);
		if(!ret)
		{//- it's now big-endian
			// assert it's little-endian
			unsigned char* lastByte = firstByte + sizeof(value);
			if(*lastByte != test)
			{//- it's not little-endian, too -----
				goto hell;
			}

			if(false)
			{
				hell:
				assert(false & !((char const* const)"Your machine is neither big-endian nor little-endian. Not supported!"));

				class DeadKitten {} up;
				throw up;
			}
		}

		return ret;
	}

	void convert2BigEndian(byte* dst, std::size_t dstCount,
	                       byte const* src, std::size_t srcCount)
	{
		static bool const IS_BIG_ENDIAN = isBigEndian();

		if(IS_BIG_ENDIAN)
		{
			memcpy
			(
				reinterpret_cast < void* >(dst),
				reinterpret_cast < void const* >(src),
				std::min(dstCount, srcCount)
			);
		}else
		{
			assert(0 == dstCount % 2);
			assert(0 == srcCount % 2);

			for(std::size_t i = 0;
				i < std::min(dstCount, srcCount);
				++i)
			{
				dst[dstCount - i - 1] = src[i];
			}
		}

		for(std::size_t i = srcCount; i < dstCount; ++i)
		{
			dst[i] = 0;
		}

		return;
	}


	std::ostream& operator <<(std::ostream& p_os, BitmapHeader const& p)
	{
		byte data[14];
		byte* pData = data;

		//+ headerField
			std::copy( p.headerField, p.headerField + 2, pData );
			pData += sizeof(p.headerField);
		//- headerField

		//+ fileSize
			std::size_t count = 4;
			convert2BigEndian
			(
				pData, count,
				reinterpret_cast < byte const* >(&p.fileSize), sizeof(p.fileSize)
			);
			pData += count;
		//- fileSize

		//+ reserved0
			count = sizeof(p.reserved0);
			convert2BigEndian
			(
				pData, count,
				reinterpret_cast < byte const* >(p.reserved0), sizeof(p.reserved0)
			);
			pData += count;
		//- reserved0

		//+ reserved1
			count = sizeof(p.reserved1);
			convert2BigEndian
			(
				pData, count,
				reinterpret_cast < byte const* >(p.reserved1), sizeof(p.reserved1)
			);
			pData += count;
		//- reserved1

		//+ dataOffset
			count = sizeof(p.dataOffset);
			convert2BigEndian
			(
				pData, count,
				reinterpret_cast < byte const* >(&p.dataOffset), sizeof(p.dataOffset)
			);
			pData += count;
		//- dataOffset

		assert(data + sizeof(data) == pData);

		// write to stream
		p_os.write( data, (int)sizeof(data) );

		return p_os;
	}


	std::ostream& operator <<(std::ostream& p_os, BITMAPINFOHEADER const& p)
	{
		static uint_least32_t const BITMAPINFOHEADER_SIZE = 40;
		byte data[BITMAPINFOHEADER_SIZE];
		byte* pData = data;

		std::size_t count = 0;

		//+ BITMAPINFOHEADER_SIZE
			count = 4;
			convert2BigEndian
			(
				pData, count,
				reinterpret_cast < byte const* >( &BITMAPINFOHEADER_SIZE ), sizeof(BITMAPINFOHEADER_SIZE)
			);
			pData += count;
		//- BITMAPINFOHEADER_SIZE

		//+ width
			count = 4;
			convert2BigEndian
			(
				pData, count,
				reinterpret_cast < byte const* >( &p.width ), sizeof(p.width)
			);
			pData += count;
		//- width
		//+ height
			count = 4;
			convert2BigEndian
			(
				pData, count,
				reinterpret_cast < byte const* >( &p.height ), sizeof(p.height)
			);
			pData += count;
		//- height

		//+ color planes
			static uint_least16_t const COLOR_PLANES = 1;

			count = 2;
			convert2BigEndian
			(
				pData, count,
				reinterpret_cast < byte const* >( &COLOR_PLANES ), sizeof(COLOR_PLANES)
			);
			pData += count;
		//- color planes

		//+ bitsPP
			count = 2;
			convert2BigEndian
			(
				pData, count,
				reinterpret_cast < byte const* >( &p.bitsPP ), sizeof(p.bitsPP)
			);
			pData += count;
		//- bitsPP

		//+ compressionType
			count = 4;
			convert2BigEndian
			(
				pData, count,
				reinterpret_cast < byte const* >( &p.compressionType ), sizeof(p.compressionType)
			);
			pData += count;
		//- compressionType

		//+ bmpDataSize
			count = 4;
			convert2BigEndian
			(
				pData, count,
				reinterpret_cast < byte const* >( &p.bmpDataSize ), sizeof(p.bmpDataSize)
			);
			pData += count;
		//- bmpDataSize

		//+ hres
			count = 4;
			convert2BigEndian
			(
				pData, count,
				reinterpret_cast < byte const* >( &p.hres ), sizeof(p.hres)
			);
			pData += count;
		//- hres
		//+ vres
			count = 4;
			convert2BigEndian
			(
				pData, count,
				reinterpret_cast < byte const* >( &p.vres ), sizeof(p.vres)
			);
			pData += count;
		//- vres

		//+ nColors
			count = 4;
			convert2BigEndian
			(
				pData, count,
				reinterpret_cast < byte const* >( &p.nColors ), sizeof(p.nColors)
			);
			pData += count;
		//- nColors
		//+ nImportantColors
			count = 4;
			convert2BigEndian
			(
				pData, count,
				reinterpret_cast < byte const* >( &p.nImportantColors ), sizeof(p.nImportantColors)
			);
			pData += count;
		//- nImportantColors

		assert(data + sizeof(data) == pData);

		p_os.write( data, sizeof(data) );

		return p_os;
	}
}
