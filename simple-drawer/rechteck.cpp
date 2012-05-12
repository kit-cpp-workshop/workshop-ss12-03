#include "rechteck.h"
#include "line.h"

#include <cmath>
#include <iostream>

namespace bmp
{
	bool drawrechteck::draw(BatchBitmap24& p_target, RelativeCoordinate p1, RelativeCoordinate p2,
			RelativeCoordinate p3,RelativeCoordinate p4, Color24 p_color)
	{
		bmp::lineto l1(p2);
		if (!l1.applyTo(p_target))
		{
			std::cout << "Error" << std::endl;
		}

		bmp::lineto l2(p3);
		if (!l2.applyTo(p_target))
		{
			std::cout << "Error" << std::endl;
		}

		bmp::lineto l3(p4);
		if (!l3.applyTo(p_target))
		{
			std::cout << "Error" << std::endl;
		}

		bmp::lineto l4(p1);
		if (!l4.applyTo(p_target))
		{
			std::cout << "Error" << std::endl;
		}

		return true;
	}




	rechteck::rechteck(bmp::RelativeCoordinate co2,bmp::RelativeCoordinate co3,bmp::RelativeCoordinate co4)
	{
		p2=co2;
		p3=co3;
		p4=co4;
	}

	rechteck::~rechteck()
	{
		/* does not require to do anything special in this implementation */
	}

	bool rechteck::applyTo(bmp::BatchBitmap24& p)
	{
		drawrechteck rechteckObj;
		rechteckObj.draw(p,(p.getCurrentPos()).convert(),p2,p3,p4,p.getCurrentColor());

		return true;
	}
}
