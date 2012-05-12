#include "line.h"

#include <cmath>
#include <iostream>


namespace bmp
{
	bool line::draw(Bitmap24& p_target, AbsoluteCoordinate p_from, AbsoluteCoordinate p_to, Color24 p_color)
	{
		if(!p_from.refersTo(p_target) || !p_to.refersTo(p_target))
		{
			return false;
		}

		unsigned int startx=p_from.getX();
		unsigned int starty=p_from.getY();
		unsigned int endx=p_to.getX();
		unsigned int endy=p_to.getY();


		std::cout << "From " << startx << ":" << starty << " to " << endx << ":" << endy <<std::endl;


		unsigned int currentx;
		unsigned int currenty;


		p_target.setPixel(startx, starty, p_color);
		p_target.setPixel(endx, endy, p_color);

		double winkel;
		if (endx!=startx)
		{
			winkel=atan((double(endy)-double(starty))/(double(endx)-double(startx)));
		}

		else
		{
			winkel=2*std::atan(1); //Pi/2
		}



		for (int i=0;i<=ceil(sqrt((endy-starty)*(endy-starty)+(endx-startx)*(endx-startx)));i++)
		{
			if (endx>=startx)
			{
				currentx=round(startx+i*cos(winkel));
			}
			else
			{
				currentx=round(startx-i*cos(winkel));
			}

			if (endy>=starty)
			{
				currenty=round(starty+i*std::abs(sin(winkel)));
			}
			else
			{
				currenty=round(starty-i*std::abs(sin(winkel)));
			}

			p_target.setPixel(currentx, currenty, p_color);
		}

		// please IMPLEMENT here!!


		return true;
	}




	lineto::lineto(bmp::RelativeCoordinate p_to)
		: to( p_to )
	{}

	lineto::~lineto()
	{
		/* does not require to do anything special in this implementation */
	}

	bool lineto::applyTo(bmp::BatchBitmap24& p)
	{
		line lineObj;
		AbsoluteCoordinate absTo = to.convert(p);

		if( ! lineObj.draw(p, p.getCurrentPos(), absTo, p.getCurrentColor()) )
		{
			return false;
		}

		return p.setCurrentPos( absTo );
	}
}
