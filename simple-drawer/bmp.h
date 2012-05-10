#ifndef H_BMP
#define H_BMP




#include <string>
#include "bmpheader.h"



// NOTE: const correctness is NOT enforced here!


namespace bmp
{
	// a simple structure (an aggregate) that contains a color in RGB format
	// every color part (R, G, B) shall be in [0, 255]
	struct Color24
	{
		byte red;
		byte green;
		byte blue;

		bool equals(Color24 p);
	};


	// The bitmap class
	// as we use 24 bits per pixel here, we call it Bitmap24
	class Bitmap24
	{
	public:
		// just a constant that is used internally, 24/8 = 3
		static unsigned int const bytesPerPixel = 3;


		// create the bitmap with a fixed width and height
		Bitmap24(unsigned int p_width, unsigned int p_height);
		virtual ~Bitmap24();

		// simple accessors to width and height properties
		unsigned int getWidth();
		unsigned int getHeight();

		// accessors to single pixels, a pixel is just a Color24 at a certain coordinate
		// NOTE: the origin of the coordinate system is the TOP LEFT corner
		// returns false in case of error (coordinate outside bitmap range)
		bool getPixel(unsigned int p_x, unsigned int p_y, /*out*/ Color24& p_c);
		bool setPixel(unsigned int p_x, unsigned int p_y, /*in */ Color24  p_c);

		// write the bitmap to a file
		void save(std::string p_name);


	private:
		// internal method used to compute the array index from a coordinate
		bool getIndex(unsigned int p_x, unsigned int p_y, unsigned int& p_index);


		// the bitmap itself, an array containing some sort of 2-dimensional map of pixels
		// using a Pixel24* seems useful at first glance, but there might be alignment issues
		byte* bitmap;	// NOTE: each row is aligned at a 4-byte boundary

		// the effective size of a row, including alignment
		unsigned int rowSize;	// in [byte]

		unsigned int width;
		unsigned int height;
	};
}




#endif
