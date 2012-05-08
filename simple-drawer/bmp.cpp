#include <fstream>
#include <utility>

#include "bmp.h"
#include "batchbmp.h"


namespace bmp
{
	// WTF?
	//unsigned int const Bitmap24::bytesPerPixel;


	// the Pixel24 is an accessor only!
	struct Pixel24
	{
	public:
		byte& red;
		byte& green;
		byte& blue;

		void setColor(Color c);
		Color getColor();

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

	void Pixel24::setColor(Color c)
	{
		red = c.red;
		green = c.green;
		blue = c.blue;
	}
	Color Pixel24::getColor()
	{
		return Color(red, green, blue);
	}




	Bitmap24::Bitmap24()
		: bitmap(0)
	{}

	Bitmap24::~Bitmap24()
	{
		delete[] bitmap;
	}

	bool Bitmap24::create(unsigned int p_width, unsigned int p_height)
	{
		if(bitmap)
		{
			return false;
		}
		
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

		return true;
	}


	unsigned int Bitmap24::getWidth()
	{
		return width;
	}
	unsigned int Bitmap24::getHeight()
	{
		return height;
	}


	Color Bitmap24::getPixel(unsigned int x, unsigned int y)
	{
		if(!bitmap)
		{
			// what now?
			throw 42;
		}else
		{
			if(x >= width || y >= height)
			{
				// what now?
				throw 42;
			}

			// consider alignment
			unsigned int index = y * rowSize + x * bytesPerPixel;

			return Pixel24(bitmap + index).getColor();
		}
	}
	void Bitmap24::setPixel(unsigned int x, unsigned int y, Color c)
	{
		if(!bitmap)
		{
			// what now?
			throw 42;
		}else
		{
			if(x >= width || y >= height)
			{
				// what now?
				throw 42;
			}

			// consider alignment
			unsigned int index = y * rowSize + x * bytesPerPixel;

			Pixel24(bitmap + index).setColor(c);
		}
	}


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
		}


		static BITMAPINFOHEADER const DEFAULT_BITMAPHEADER =
		{
			0, 0,   // width, height
			24,     // bits per pixel
			BI_RGB, // compression type
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
		// 14 == size of header, 40 == size of bitmap info header
		specificHeader.fileSize = 14 + 40 + specificBitmapHeader.bmpDataSize;
		specificHeader.dataOffset = 14 + 40;

		out << specificHeader;
		out << specificBitmapHeader;

		out.write( reinterpret_cast<const char* const>(bitmap), rowSize*width*height );

		out.flush();
	}
}
