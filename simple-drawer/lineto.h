#include "drawable.h"
#include "batchbmp.h"

class lineto
	: public bmp::Drawable
{
public:
	lineto(bmp::AbsoluteCoordinate p);
	virtual ~lineto();

	virtual bool apply(bmp::BatchBitmap24& p);

private:
	bmp::AbsoluteCoordinate to;
};
