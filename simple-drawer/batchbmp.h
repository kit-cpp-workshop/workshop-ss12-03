#ifndef H_BATCHBITMAP24
#define H_BATCHBITMAP24




#include "bmp.h"
#include "coordinate.h"


namespace bmp
{
    /**
     * BatchBitmap24 extends Bitmap24 by some convience features for remembering
     * a (for example the last) color and a position, which might be used to
     * simplyfiy some drawing operations.
     *
     * All drawing operations can now be performed using AbsoluteCoordinate
     * instances. The valid coordinate range is inherited from Bitmap24.
     */
	class BatchBitmap24
		: public Bitmap24
	{
	public:
        /**
        * Creates a new RGB 24-bit bitmap instance with the passed dimensions,
        * featuring some additional convenience features.
        *
        * @param p_width the width of the new bitmap, in pixels
        * @param p_height the height of the new bitmap, in pixels
        */
		BatchBitmap24(unsigned int p_width, unsigned int p_height);
		/**
		 * Destroys the bitmap and releases all allocated resources.
		 */
		virtual ~BatchBitmap24();


		/**
         * Returns the color value of the pixel at coordinates p_coord by using
         * the passed reference p_color . If the coordinates are invalid (do not
         * refer to this instance), false is returned, else true.
         *
		 * @param p_coord the pixel's coordinates
		 * @param p_color a reference to a Color24 instance which should be set
		 *                to the pixels color value
         * @return true if the coordinates are valid, else false
		 */
		bool getPixelByCoord(AbsoluteCoordinate p_coord, /*out*/ Color24& p_color);
		/**
		 * Sets the color value of the pixel at coordinates p_coord to the the
		 * value of p_color. If the coodinates are invalid (do not refer to this
		 * instance), false is returned, else true.
		 *
		 * @param p_coord the coordinates of the pixel to change
		 * @param p_color the new pixel color to set
		 * @return true if the coordinates are valid, else false
		 */
		bool setPixelByCoord(AbsoluteCoordinate p_coord, /*in */ Color24  p_color);


		/**
		 * Sets the brush position to the passed value. If the value is invalid,
		 * false is returned, else true.
		 *
		 * @param p the brus position to set
		 * @return true if the position has been set, false if the coordinates
		 *         are invalid
		 */
		bool setCurrentPos(AbsoluteCoordinate p);
		/**
		 * Returns the least recently set brush position.
		 *
		 * @return the current brush position
		 */
		AbsoluteCoordinate getCurrentPos();

		/**
		 * Returns the most recently set brush color value.
		 *
		 * @return the current brush color value
		 */
		Color24 getCurrentColor();
		/**
		 * Sets the brush color to the passed value.
		 *
		 * @param c the brush color to set
		 */
		void setCurrentColor(Color24 c);


	private:
		/**
		 * The least recently set brush position.
		 */
		AbsoluteCoordinate currentPos;
		/**
		 * The least recently set brush color.
		 */
		Color24 currentColor;
	};
}




#endif
