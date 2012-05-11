#include <algorithm>	// for min, max
#include "bmpheader.h"


namespace bmp
{
	bool isLittleEndian()
	{
		assert(1 == sizeof(unsigned char));

		uint_least32_t value = 1;
		unsigned char* firstByte = reinterpret_cast<unsigned char*>( &value );
		unsigned char test = 1;

		bool ret = (*firstByte == test);
		if(!ret)
		{//- it's not little-endian
			//! assert it's big-endian
			unsigned char* lastByte = firstByte + sizeof(value);
			if(*lastByte != test)
			{//- it's not big-endian, too -----
				goto hell;
			}

			if(false)
			{
				hell:
				assert(false && "Your machine is neither little-endian nor big-endian. Not supported!");

				class DeadKitten {} up;
				throw up;
			}
		}

		return ret;
	}

	void convert2BigEndian(byte* dst, std::size_t dstCount,
	                       byte const* src, std::size_t srcCount)
	{
		static bool const IS_LITTLE_ENDIAN = isLittleEndian();

		if(IS_LITTLE_ENDIAN)
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

	// scalar version
	template < typename _T >
	byte* insertAsBigEndian(byte* where, std::size_t howManyBytes, _T const what)
	{
		convert2BigEndian
		(
			where, howManyBytes,
			reinterpret_cast < byte const* >(&what), sizeof(what)
		);

		return where + howManyBytes;
	}
	// array version
	template < typename _T, std::size_t _arrayCount >
	byte* insertAsBigEndian(byte* where, std::size_t howManyBytesPerElement, _T const (&what)[_arrayCount])
	{
		for(std::size_t i = 0; i < _arrayCount; ++i)
		{
			where = insertAsBigEndian(where, howManyBytesPerElement, what[i]);
		}

		return where;
	}




	std::ostream& operator <<(std::ostream& p_os, bmp::BitmapHeader const& p)
	{
		byte data[p.SIZE];
		byte* pData = data;


		pData = insertAsBigEndian(pData, 1, p.headerField);

		pData = insertAsBigEndian(pData, 4, p.fileSize);

		pData = insertAsBigEndian(pData, 1, p.reserved0);
		pData = insertAsBigEndian(pData, 1, p.reserved1);

		pData = insertAsBigEndian(pData, 4, p.dataOffset);


		assert(data + sizeof(data) == pData);

		// write to stream
		p_os.write( data, (int)sizeof(data) );

		return p_os;
	}


	std::ostream& operator <<(std::ostream& p_os, bmp::BITMAPINFOHEADER const& p)
	{
		byte data[p.SIZE];
		byte* pData = data;


		pData = insertAsBigEndian(pData, 4, p.SIZE);

		pData = insertAsBigEndian(pData, 4, p.width);
		pData = insertAsBigEndian(pData, 4, p.height);

		static uint_least16_t const COLOR_PLANES = 1;
		pData = insertAsBigEndian(pData, 2, COLOR_PLANES);

		pData = insertAsBigEndian(pData, 2, p.bitsPP);

		pData = insertAsBigEndian(pData, 4, p.compressionType);

		pData = insertAsBigEndian(pData, 4, p.bmpDataSize);

		pData = insertAsBigEndian(pData, 4, p.hres);
		pData = insertAsBigEndian(pData, 4, p.vres);

		pData = insertAsBigEndian(pData, 4, p.nColors);
		pData = insertAsBigEndian(pData, 4, p.nImportantColors);


		assert(data + sizeof(data) == pData);

		p_os.write( data, sizeof(data) );

		return p_os;
	}
}
