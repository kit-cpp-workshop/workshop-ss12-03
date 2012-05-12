#ifndef RECHTECK_H
#define RECHTECK_H

#include "drawable.h"
#include "batchbmp.h"


namespace bmp
{
	// never mind the following comment, it continues the black voodoo from drawable.h
	// when we would have introduced IDrawable, class line had to inherit from:
	// public virtual IDrawable
	// and would need a virtual dtor



	class drawrechteck
	{
	public:
		// returns false in case of error (one of the coordinates does not refer to the target)
		bool draw(bmp::BatchBitmap24& p_target,
				RelativeCoordinate p1, RelativeCoordinate p2, RelativeCoordinate p3, RelativeCoordinate p4, Color24 p_color);
	};


	//Klasse zur Verwaltung von Dreiecken
	class rechteck
		: public IBatchDrawable
	{
	public:
		rechteck(bmp::RelativeCoordinate p2,bmp::RelativeCoordinate p3,bmp::RelativeCoordinate p4);
		virtual ~rechteck();

		virtual bool applyTo(bmp::BatchBitmap24& p);

	private:
		// NOTE: we use relative coordinates here to stay independent
		//       from the bitmap which the lineto is later applied to
		bmp::RelativeCoordinate p2,p3,p4;
	};
}
#endif
