#include "lineto.h"

#include <cmath>


lineto::lineto(bmp::AbsoluteCoordinate p)
	: to( p )
{}
lineto::~lineto()
{}

bool lineto::apply(bmp::BatchBitmap24& p)
{
	bmp::RelativeCoordinate curr = p.getCurrentPos().convert();
	bmp::RelativeCoordinate end = to.convert();
		
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

		bmp::AbsoluteCoordinate currPxAbs = currPxRel.convert(p);

		p.setPixel(currPxAbs, p.getCurrentColor());
	}

	return true;
}
