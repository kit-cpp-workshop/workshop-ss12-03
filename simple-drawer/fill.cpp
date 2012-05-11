#include "fill.h"

#include <cmath>


namespace bmp
{
	bool fillcolor::draw(Bitmap24& p_target, Color24 p_color)
	{
		for(unsigned int iRow = 0; iRow < p_target.getHeight(); ++iRow)
		{
			for(unsigned int iColumn = 0; iColumn < p_target.getWidth(); ++iColumn)
			{
				p_target.setPixel(iColumn, iRow, p_color);
			}
		}

		return true;
	}




	fillp::fillp()
	{
	/* Constructur not necessary */
	}

	fillp::~fillp()
	{
		/* does not require to do anything special in this implementation */
	}

	bool fillp::applyTo(bmp::BatchBitmap24& p)
	{
		bmp::fillcolor fillObj;
		if (fillObj.draw(p,p.getCurrentColor()))
		{
			return false;
		}
		return true;
	}
}
