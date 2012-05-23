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

	bool lineto::applyTo(bmp::BatchBitmap24& p_target)
	{
		line lineObj;

		// we draw a line from the current "pen"'s position
		AbsoluteCoordinate absFrom = p_target.getCurrentPos();

		// we stored a RelativeCoordinate to stay independent from a concrete bitmap
		// now, we do have a concrete bitmap
		AbsoluteCoordinate absTo = to.convert(p_target);

		// we draw the line using the current "pen"'s color
		Color24 color = p_target.getCurrentColor();

		// use the algorithm implemented more generally in the line class
		if( ! lineObj.draw(p_target, absFrom, absTo, color) )
		{
			return false;
		}

		return p_target.setCurrentPos( absTo );
	}
}
