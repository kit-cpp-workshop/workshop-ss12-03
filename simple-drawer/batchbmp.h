#ifndef H_BATCHBITMAP24
#define H_BATCHBITMAP24




#include <istream>
#include <utility>
#include "bmp.h"
#include "coordinate.h"


namespace bmp
{
	// a bitmap plus a current color and a current position
	class BatchBitmap24
		: public Bitmap24
	{
	public:
		BatchBitmap24(unsigned int p_width, unsigned int p_height);
		virtual ~BatchBitmap24();


		// the batch bitmap class allows the use of an AbsoluteCoordinate
		// returns false in case of error (coordinate does not refer to this bitmap)
		bool getPixelByCoord(AbsoluteCoordinate p_coord, /*out*/ Color24& p_color);
		bool setPixelByCoord(AbsoluteCoordinate p_coord, /*in */ Color24  p_color);


		// accessors for the current position
		// returns false in case of error (coordinate does not refer to this bitmap)
		bool setCurrentPos(AbsoluteCoordinate p);
		AbsoluteCoordinate getCurrentPos();

		// accessors for the current color
		Color24 getCurrentColor();
		void setCurrentColor(Color24 c);


	private:
		AbsoluteCoordinate currentPos;
		Color24 currentColor;
	};
}




#endif
