#include "batchbmp.h"
#include "lineto.h"


int main()
{
	bmp::BatchBitmap24 blackBitmap;

	blackBitmap.create(10, 10);

	bmp::Color blue(0, 0, 255);

	for(unsigned int iRow = 0; iRow < blackBitmap.getHeight(); ++iRow)
	{
		for(unsigned int iColumn = 0; iColumn < blackBitmap.getWidth(); ++iColumn)
		{
			blackBitmap.Bitmap24::setPixel(iColumn, iRow, blue);
		}
	}

	bmp::AbsoluteCoordinate end(blackBitmap);
	end.set(9, 5);
	lineto myLine( end );

	myLine.apply(blackBitmap);


	blackBitmap.save("foo.bmp");

	return 0;
}
