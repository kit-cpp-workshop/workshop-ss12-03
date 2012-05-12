#ifndef DREIECK_H
#define DREIECK_H

#include "drawable.h"
#include "batchbmp.h"


namespace bmp
{
	// never mind the following comment, it continues the black voodoo from drawable.h
	// when we would have introduced IDrawable, class line had to inherit from:
	// public virtual IDrawable
	// and would need a virtual dtor



	class drawdreieck
	{
	public:
		// returns false in case of error (one of the coordinates does not refer to the target)
		bool draw(bmp::BatchBitmap24& p_target,
				RelativeCoordinate p1, RelativeCoordinate p2, RelativeCoordinate p3, Color24 p_color);
	};


	//Klasse zur Verwaltung von Dreiecken
	class dreieck
		: public IBatchDrawable
	{
	public:
		dreieck(bmp::RelativeCoordinate p2,bmp::RelativeCoordinate p3);
		virtual ~dreieck();

		virtual bool applyTo(bmp::BatchBitmap24& p);

	private:
		// NOTE: we use relative coordinates here to stay independent
		//       from the bitmap which the lineto is later applied to
		bmp::RelativeCoordinate p2,p3;
	};
}
#endif
