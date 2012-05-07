#ifndef H_BMP
#define H_BMP




#include <string>
#include "bmpheader.h"



// NOTE: const correctness is NOT enforced here!


namespace bmp
{
	class Bitmap24;
	class BatchBitmap24;
	class RelativeCoordinate;
	struct Color;
}


std::istream& operator >>(std::istream& p_o, bmp::RelativeCoordinate& p_c);


namespace bmp
{
	class Bitmap24	// 24 bits per pixel
	{
	public:
		static unsigned int const bytesPerPixel = 3;


		Bitmap24();
		virtual ~Bitmap24();

		bool create(unsigned int p_width, unsigned int p_height);

		unsigned int getWidth();
		unsigned int getHeight();

		Color getPixel(unsigned int x, unsigned int y);
		void setPixel(unsigned int x, unsigned int y, Color c);

		void save(std::string name);


	private:
		// using a Pixel24 object seems useful at first glance, but there might be alignment issues
		byte* bitmap;	// NOTE: each row is aligned at a 4-byte boundary
		unsigned int width;
		unsigned int height;
		unsigned int rowSize;	// in [byte]
	};
}




#endif
