#include "batchbmp.h"
#include "line.h"
#include "fill.h"
#include "dreieck.h"
#include "rechteck.h"
#include <iostream>


int main()
{
	bmp::BatchBitmap24 blackBitmap(10, 10);

	bmp::Color24 blue = {0, 0, 255};
	bmp::Color24 red = {255,0,0};
	bmp::Color24 green = {0, 255, 0};
	bmp::Color24 yellow = {255, 255, 0};

	//Hintergrundfarbe blau
	blackBitmap.setCurrentColor(blue);
	bmp::fillp myBackground;
	myBackground.applyTo(blackBitmap);


	// Linie zeichnen
	bmp::AbsoluteCoordinate end(blackBitmap);
	if(!end.set(9, 5))
	{
		std::cout << "error!" << std::endl;
	}else
	{
		blackBitmap.setCurrentColor(red);
		bmp::lineto myLine( end.convert() );
		//myLine.applyTo(blackBitmap);
	}

	// Dreieck zeichnen
	{
		blackBitmap.setCurrentColor(green);

		bmp::RelativeCoordinate p1,p2,p3;

		p1.set(0.2,0.2);
		p2.set(0.2,0.8);
		p3.set(0.8,0.5);

		//Anfangswert setzen
		bmp::AbsoluteCoordinate a1=p1.convert(blackBitmap);
		blackBitmap.setCurrentPos(a1);

		bmp::dreieck myDreieck(p2,p3);
		//myDreieck.applyTo(blackBitmap);
	}


	// Rechteck zeichnen
	{
		blackBitmap.setCurrentColor(yellow);

		bmp::RelativeCoordinate p1,p2,p3,p4;

		p1.set(0.2,0.2);
		p2.set(0.2,0.8);
		p3.set(0.8,0.8);
		p4.set(0.8,0.2);

		//Anfangswert setzen
		bmp::AbsoluteCoordinate a1=p1.convert(blackBitmap);
		blackBitmap.setCurrentPos(a1);

		bmp::rechteck myRechteck(p2,p3,p4);
		myRechteck.applyTo(blackBitmap);
	}

 	blackBitmap.save("foo.bmp");


	return 0;
}

