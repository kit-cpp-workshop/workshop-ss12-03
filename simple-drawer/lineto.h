#include "drawable.h"
#include "batchbmp.h"

class lineto
{
public:
	lineto(bmp::AbsoluteCoordinate p);

	virtual bool apply(bmp::BatchBitmap24& p);

private:
	bmp::AbsoluteCoordinate to;
};
