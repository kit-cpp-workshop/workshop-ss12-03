#ifndef H_BMP
#define H_BMP




#include <string>
#include "bmp-types.h"
#include "bmpheader.h"



// (Unimportant) NOTE: const correctness is NOT enforced here!


namespace bmp
{
	// a simple structure (an aggregate) that contains a color in RGB format
	// every color part (R, G, B) shall be in [0, 255]
    /**
     * This struct encapsulates the color information of a 24 Bit RGB pixel.
     *
     * The valid range for each of the three color channels (R, G, B) goes from
     * 0 to 255.
     */
	struct Color24
	{
		byte red;
		byte green;
		byte blue;

		bool equals(Color24 p);
	};


	/**
	 * This class provides a bitmap based canvas to draw onto. The bitmap
	 * stores three color channels of each 8 bits.
	 */
	class Bitmap24
	{
	public:
		// just a constant that is used internally, 24/8 = 3
		static unsigned int const bytesPerPixel = 3;


		/**
		 * Creates a new RGB 24-bit bitmap instance with the passed dimensions.
		 *
		 * The individual pixels can be accessed by getPixel() and  setPixel().
		 * The coordinate system is originated at the top left corner and the
		 * coordinate axes point to the lower respective right edge of the
		 * screen. The coordinate value range starts at (0, 0) and ends at
		 * (p_width - 1, p_height - 1).
		 *
		 * @param p_width the width of the new bitmap, in pixels
		 * @param p_height the height of the new bitmap, in pixels
		 */
		Bitmap24(unsigned int p_width, unsigned int p_height);
		/**
		 * Destroy the bitmap and releases all ressources.
		 */
		virtual ~Bitmap24();

		/**
		 * Returns the width of this bitmap.
		 *
		 * @return the width of this bitmap
		 */
		unsigned int getWidth();
		/**
		 * Returns the height of this bitmap.
		 *
		 * @return the height of this bitmap.
		 */
		unsigned int getHeight();

		/**
		 * Returns the color value of the pixel at coordinate (p_x, p_y) by
		 * using the passed reference p_c . If the coordinate is out of range,
		 * true is returned, else false
		 *
		 * @param p_x the X coordinate component
		 * @param p_y the Y coordinate component
		 * @param p_c a reference to a Color24 instance which should be set to
		 *            the pixels color value
		 * @return true if the coordinates are in range, else false
		 */
		bool getPixel(unsigned int p_x, unsigned int p_y, /*out*/ Color24& p_c);
		/**
         * Sets the color value of the pixel at coordinate (p_x, p_y) to the
         * value passed by p_c. If the coordinate is out of range, true is
         * returned, else false
         *
         * @param p_x the X coordinate component
         * @param p_y the Y coordinate component
         * @param p_c the new pixel color to set
         * @return true if the coordinates are in range, else false
         */
		bool setPixel(unsigned int p_x, unsigned int p_y, /*in */ Color24  p_c);

		/**
		 * Saves the current canvas as bitmp (.bmp) at the passed path. If just
		 * a filename is provided, the bitmap will be saved in the current
		 * working directory.
		 *
		 * @param p_name the path/filename to which the bitmap should be written
		 */
		void save(std::string p_name);


	private:
		/**
		 * @internal
		 *
		 * This magic function calculates the offset of the pixel with
		 * coordinates (p_x, p_y) in the linear byte array in 24-bit bitmap
		 * format.
		 *
		 * @param p_x the X coordinate component
		 * @param p_y the Y coordinate component
		 * @param p_index the calculated absolute offset in bytes
		 * @return true if the passed coordinates are in range, else false
		 */
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




#endif	// H_BMP
