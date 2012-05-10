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


		// NOTE: we use relative coordinates here for pure algorithmic reasons

		bmp::RelativeCoordinate curr = p_from.convert();
		bmp::RelativeCoordinate end = p_to.convert();

		double dirX = end.getX() - curr.getX();
		double dirY = end.getY() - curr.getY();

		double length = std::sqrt(dirX*dirX + dirY*dirY);

		dirX /= length;
		dirY /= length;

		// well, err, this is no good??
		for(double step = 0; step <= length; step += 0.05)
		{
			bmp::RelativeCoordinate currPxRel;
			currPxRel.set
			(
				curr.getX() + dirX * step,
				curr.getY() + dirY * step
			);

			bmp::AbsoluteCoordinate currPxAbs = currPxRel.convert(p_target);

			p_target.setPixel( currPxAbs.getX(), currPxAbs.getY(), p_color );
		}


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
