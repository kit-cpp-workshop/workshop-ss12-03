#include "batchbmp.h"
#include <cassert>


// magic, don't care
std::istream& operator >>(std::istream& p_i, bmp::RelativeCoordinate p_c)
{
	double x = 0;
	double y = 0;
	p_i >> x;
	p_i >> y;

	if(p_i.good())
	{
		bmp::RelativeCoordinate temp;
		temp.set(x, y);

		std::swap(p_c, temp);
	}

	return p_i;
}


namespace bmp
{
	AbsoluteCoordinate::AbsoluteCoordinate(Bitmap24& p_ref)
		: refBitmap(&p_ref)
		, x( 0 )
		, y( 0 )
	{}

	bool AbsoluteCoordinate::set(unsigned int p_x, unsigned int p_y)
	{
		if(p_x > refBitmap->getWidth() || p_y > refBitmap->getHeight())
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
		RelativeCoordinate ret;

		bool error = ret.set
		(
			static_cast<double>(x) / refBitmap->getWidth(),
			static_cast<double>(y) / refBitmap->getHeight()
		);

		assert(!error);

		return ret;
	}




	RelativeCoordinate::RelativeCoordinate()
		: x( 0 )
		, y( 0 )
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




	BatchBitmap24::BatchBitmap24(unsigned int p_width, unsigned int p_height)
		: Bitmap24( p_width, p_height )
		, currentPos( *this )
		, currentColor()	// believe it or not, this value-initializes the color elements to 0
	{
		currentPos.set(0, 0);
	}
	BatchBitmap24::~BatchBitmap24()
	{}

	void BatchBitmap24::setCurrentPos(AbsoluteCoordinate p)
	{
		currentPos = p;
	}
	AbsoluteCoordinate BatchBitmap24::getCurrentPos()
	{
		return currentPos;
	}

	bool BatchBitmap24::getPixel(AbsoluteCoordinate p_coord, Color24& p_color)
	{
		if(this != p_coord.refBitmap)
		{
			return false;
		}else
		{
			// yes, it's checked twice, actually
			return Bitmap24::getPixel( p_coord.getX(), p_coord.getY(), p_color );
		}
	}
	bool BatchBitmap24::setPixel(AbsoluteCoordinate p_coord, Color24 p_color)
	{
		if(this != p_coord.refBitmap)
		{
			return false;
		}else
		{
			// yes, it's checked twice, actually
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
