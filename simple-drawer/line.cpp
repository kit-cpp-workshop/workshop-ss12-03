#include "line.h"

#include <cmath>


namespace bmp
{
	bool line::draw(Bitmap24& p_target, AbsoluteCoordinate p_from, AbsoluteCoordinate p_to, Color24 p_color)
	{
		if(!p_from.refersTo(p_target) || !p_to.refersTo(p_target))
		{
			return false;
		}


		// please IMPLEMENT here!!


		return true;
	}




	lineto::lineto(bmp::RelativeCoordinate p_to)
		: to( p_to )
	{}

	lineto::~lineto()
	{
		/* does not require to do anything special in this implementation */
	}

	bool lineto::applyTo(bmp::BatchBitmap24& p)
	{
		line lineObj;
		AbsoluteCoordinate absTo = to.convert(p);

		if( ! lineObj.draw(p, p.getCurrentPos(), absTo, p.getCurrentColor()) )
		{
			return false;
		}

		return p.setCurrentPos( absTo );
	}
}
