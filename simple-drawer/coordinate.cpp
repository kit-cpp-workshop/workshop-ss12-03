#include <cassert>

#include "coordinate.h"
#include "bmp.h"


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

		bool success = ret.set
		(
			static_cast<double>(x) / refBitmap->getWidth(),
			static_cast<double>(y) / refBitmap->getHeight()
		);

		assert(success);

		return ret;
	}

	bool AbsoluteCoordinate::refersTo(Bitmap24& p)
	{
		return (&p == refBitmap);
	}

	bool AbsoluteCoordinate::equals(AbsoluteCoordinate p)
	{
		return (refBitmap == p.refBitmap && x == p.x && y == p.y);
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

	AbsoluteCoordinate RelativeCoordinate::convert(Bitmap24& p_ref)
	{
		AbsoluteCoordinate ret(p_ref);
		ret.set
		(
			static_cast<unsigned int>( x * p_ref.getWidth() ),
			static_cast<unsigned int>( y * p_ref.getHeight() )
		);

		return ret;
	}

	bool RelativeCoordinate::equals(RelativeCoordinate p)
	{
		return (x == p.x && y == p.y);
	}




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
}
