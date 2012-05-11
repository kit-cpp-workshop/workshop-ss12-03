#include "drawable.h"
#include "batchbmp.h"


namespace bmp
{
	// never mind the following comment, it continues the black voodoo from drawable.h
	// when we would have introduced IDrawable, class line had to inherit from:
	// public virtual IDrawable
	// and would need a virtual dtor


	// a class whose instances can fill a Bitmap24 with the current color
	// NOTE: there is a reason why this is a class (and not a simple function)
	//       but it'll only reveal in some future workshop (or you use black voodoo already now)
	class fillcolor
	{
	public:
		// returns false in case of error (one of the coordinates does not refer to the target)
		bool draw(bmp::Bitmap24& p_target, Color24 p_color);
	};


	// a class whose instances can draw lines to BatchBitmap24
	// from the current position to another coordinate
	// the current position of the bitmap is changed to the end position of the line
	class fillp
		: public IBatchDrawable
	{
	public:
		fillp();
		virtual ~fillp();

		virtual bool applyTo(bmp::BatchBitmap24& p);

	};
}
