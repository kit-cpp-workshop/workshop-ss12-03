#include <fstream>
#include <utility>

#include "bmp.h"
#include "batchbmp.h"


namespace bmp
{
	bool Color24::equals(Color24 p)
	{
		return (red == p.red && green == p.green && blue == p.blue);
	}


	// WTF?
	//unsigned int const Bitmap24::bytesPerPixel;


	// The Pixel24 struct is an internal accessor only to map the byte-array of Bitmap24
	// to the Color24 aggregate
	struct Pixel24
	{
	public:
		byte& red;
		byte& green;
		byte& blue;

		void setColor(Color24 c);
		Color24 getColor();

	private:
		friend class Bitmap24;
		Pixel24(byte* p_bitmap);
	};

	// NOTE: yes, it's reversed..
	Pixel24::Pixel24(byte* p_bitmap)
		: red  ( *(p_bitmap + 2) )
		, green( *(p_bitmap + 1) )
		, blue ( *(p_bitmap + 0) )
	{}

	void Pixel24::setColor(Color24 c)
	{
		red = c.red;
		green = c.green;
		blue = c.blue;
	}
	Color24 Pixel24::getColor()
	{
		Color24 ret = {red, green, blue};
		return ret;
	}




	Bitmap24::Bitmap24(unsigned int p_width, unsigned int p_height)
		: bitmap(0)
	{
		// consider alignment of rows at 4-byte boundary
		// NOTE: we round up here
		unsigned int const rowSizeTemp = ((bytesPerPixel * p_width + (4-1)) / 4) * 4;

		byte* const temp = new byte[rowSizeTemp * p_height];

		//+ exception-safe part, swap
			bitmap = temp;

			width = p_width;
			height = p_height;

			rowSize = rowSizeTemp;
		//- exception-safe part
	}

	Bitmap24::~Bitmap24()
	{
		delete[] bitmap;
	}


	unsigned int Bitmap24::getWidth()
	{
		return width;
	}
	unsigned int Bitmap24::getHeight()
	{
		return height;
	}


	bool Bitmap24::getIndex(unsigned int p_x, unsigned int p_y, unsigned int& p_index)
	{
		if(p_x >= width || p_y >= height)
		{
			return false;
		}

		// consider alignment
		unsigned int index = p_y * rowSize + p_x * bytesPerPixel;
		p_index = index;

		return true;
	}

	bool Bitmap24::getPixel(unsigned int p_x, unsigned int p_y, Color24& p_c)
	{
		unsigned int index = 0;
		if(!getIndex(p_x, p_y, index))
		{
			return false;
		}else
		{
			Pixel24 px( bitmap + index );
			p_c = px.getColor();

			return true;
		}
	}
	bool Bitmap24::setPixel(unsigned int p_x, unsigned int p_y, Color24 p_c)
	{
		unsigned int index = 0;
		if(!getIndex(p_x, p_y, index))
		{
			return false;
		}else
		{
			Pixel24 px( bitmap + index );
			px.setColor(p_c);

			return true;
		}
	}


	// magic for saving the bitmap, don't care
	void Bitmap24::save(std::string name)
	{
		std::ofstream out
		(
			name.c_str(),
			std::ostream::binary | std::ostream::out | std::ostream::trunc
		);
		if(!out.is_open() || !out)
		{
			// what now?
			throw 42;
		}


		static BITMAPINFOHEADER const DEFAULT_BITMAPHEADER =
		{
			0, 0,   // width, height
			24,     // bits per pixel
			BITMAPINFOHEADER::BI_RGB, // compression type
			0,      // bmpDataSize
			90, 90, // hres, vres
			0, 0    // nColors, nImportantColors
		};
		static BitmapHeader const DEFAULT_HEADER = {{'B', 'M'}, 0, {0}, {0}, 0};

		BITMAPINFOHEADER specificBitmapHeader = DEFAULT_BITMAPHEADER;
		specificBitmapHeader.bmpDataSize = rowSize*width*height;
		specificBitmapHeader.width = width;
		specificBitmapHeader.height = height;

		BitmapHeader specificHeader = DEFAULT_HEADER;
		specificHeader.dataOffset = BitmapHeader::SIZE + BITMAPINFOHEADER::SIZE;
		specificHeader.fileSize = specificHeader.dataOffset + specificBitmapHeader.bmpDataSize;

		out << specificHeader;
		out << specificBitmapHeader;

		out.write( reinterpret_cast<const char* const>(bitmap), rowSize*width*height );

		out.flush();
	}
}
