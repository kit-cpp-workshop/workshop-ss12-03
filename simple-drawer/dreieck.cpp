#include "dreieck.h"
#include "line.h"

#include <cmath>
#include <iostream>

namespace bmp
{
	bool drawdreieck::draw(BatchBitmap24& p_target, RelativeCoordinate p1, RelativeCoordinate p2,RelativeCoordinate p3, Color24 p_color)
	{
		bmp::lineto l1(p2);
		if (!l1.applyTo(p_target))
		{
			std::cout << "Error" << std::endl;
			return false;
		}

		bmp::lineto l2(p3);
		if (!l2.applyTo(p_target))
		{
			std::cout << "Error" << std::endl;
			return false;
		}

		bmp::lineto l3(p1);
		if (!l3.applyTo(p_target))
		{
			std::cout << "Error" << std::endl;
			return false;
		}

		return true;
	}




	dreieck::dreieck(bmp::RelativeCoordinate co2,bmp::RelativeCoordinate co3)
	{
		p2=co2;
		p3=co3;
	}

	dreieck::~dreieck()
	{
		/* does not require to do anything special in this implementation */
	}

	bool dreieck::applyTo(bmp::BatchBitmap24& p)
	{
		drawdreieck dreieckObj;
		bool ret=dreieckObj.draw(p,(p.getCurrentPos()).convert(),p2,p3,p.getCurrentColor());

		return ret;
	}
}
