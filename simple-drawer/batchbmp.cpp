#include "batchbmp.h"

namespace bmp
{
AbsoluteCoordinate::AbsoluteCoordinate(BatchBitmap24& p_ref)
		: refBitmap(p_ref)
	{}

	bool AbsoluteCoordinate::set(unsigned int p_x, unsigned int p_y)
	{
		if(p_x > refBitmap.getWidth() || p_y > refBitmap.getHeight())
		{
			return false;
		}else
		{
			x = p_x;
			y = p_y;

			return true;
		}
	}

	unsigned int AbsoluteCoordinate::getX()
	{
		return x;
	}
	unsigned int AbsoluteCoordinate::getY()
	{
		return y;
	}

	RelativeCoordinate AbsoluteCoordinate::convert()
	{
		return RelativeCoordinate
		(
			static_cast<double>(x) / refBitmap.getWidth(),
			static_cast<double>(y) / refBitmap.getHeight()
		);
	}

	AbsoluteCoordinate& AbsoluteCoordinate::operator =(AbsoluteCoordinate p)
	{
		/*if(static_cast<Bitmap24&>(p.refBitmap) != static_cast<Bitmap24&>(refBitmap))
		{
			// what now?
			throw 42;
		}*/

		x = p.x;
		y = p.y;

		return *this;
	}




	RelativeCoordinate::RelativeCoordinate(double p_x, double p_y)
		: x( p_x )
		, y( p_y )
	{}

	bool RelativeCoordinate::set(double p_x, double p_y)
	{
		if(   1 < p_x || 0 > p_x
			|| 1 < p_y || 0 > p_y)
		{
			return false;
		}else
		{
			x = p_x;
			y = p_y;

			return true;
		}
	}

	double RelativeCoordinate::getX()
	{
		return x;
	}
	double RelativeCoordinate::getY()
	{
		return y;
	}

	AbsoluteCoordinate RelativeCoordinate::convert(BatchBitmap24& p_ref)
	{
		AbsoluteCoordinate ret(p_ref);
		ret.set
		(
			static_cast<unsigned int>( x * p_ref.getWidth() ),
			static_cast<unsigned int>( y * p_ref.getHeight() )
		);

		return ret;
	}




	BatchBitmap24::BatchBitmap24()
		: currentPos( *this )
		, currentColor( 0, 0, 0 )
	{
		currentPos.set(0, 0);
	}
	BatchBitmap24::~BatchBitmap24()
	{}

	void BatchBitmap24::setCurrentPos(RelativeCoordinate p)
	{
		currentPos = p.convert(*this);
	}
	RelativeCoordinate BatchBitmap24::getCurrentPos()
	{
		return currentPos.convert();
	}
	void BatchBitmap24::setCurrentPosAbs(AbsoluteCoordinate p)
	{
		currentPos = p;
	}
	AbsoluteCoordinate BatchBitmap24::getCurrentPosAbs()
	{
		return currentPos;
	}

	Pixel24 BatchBitmap24::getPixel(AbsoluteCoordinate p)
	{
		// TODO: check on origin of p?
		return Bitmap24::getPixel( p.getX(), p.getY() );
	}

	Color BatchBitmap24::getCurrentColor()
	{
		return currentColor;
	}
	void BatchBitmap24::setCurrentColor(Color c)
	{
		currentColor = c;
	}
}
