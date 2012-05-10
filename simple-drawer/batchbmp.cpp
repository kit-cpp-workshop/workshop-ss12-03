#include "batchbmp.h"


namespace bmp
{
	BatchBitmap24::BatchBitmap24(unsigned int p_width, unsigned int p_height)
		: Bitmap24( p_width, p_height )
		, currentPos( *this )
		, currentColor()	// believe it or not, this value-initializes the color members to 0 (12.6.2:3, 8.5:5 etc.)
	{
		currentPos.set(0, 0);
	}
	BatchBitmap24::~BatchBitmap24()
	{}

	bool BatchBitmap24::setCurrentPos(AbsoluteCoordinate p_coord)
	{
		if(!p_coord.refersTo(*this))
		{
			return false;
		}else
		{
			currentPos = p_coord;

			return true;
		}
	}
	AbsoluteCoordinate BatchBitmap24::getCurrentPos()
	{
		return currentPos;
	}

	bool BatchBitmap24::getPixelByCoord(AbsoluteCoordinate p_coord, Color24& p_color)
	{
		if(!p_coord.refersTo(*this))
		{
			return false;
		}else
		{
			return Bitmap24::getPixel( p_coord.getX(), p_coord.getY(), p_color );
		}
	}
	bool BatchBitmap24::setPixelByCoord(AbsoluteCoordinate p_coord, Color24 p_color)
	{
		if(!p_coord.refersTo(*this))
		{
			return false;
		}else
		{
			return Bitmap24::setPixel( p_coord.getX(), p_coord.getY(), p_color );
		}
	}

	Color24 BatchBitmap24::getCurrentColor()
	{
		return currentColor;
	}
	void BatchBitmap24::setCurrentColor(Color24 c)
	{
		currentColor = c;
	}
}
