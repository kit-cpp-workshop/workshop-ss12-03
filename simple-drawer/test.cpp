#include <iostream>

#include "test.h"


namespace bmp
{
	bool performTests(BatchBitmap24& p_bitmap, BatchBmpTest** p_ppTests, unsigned int p_testCount)
	{
		bool passed = true;
		for(unsigned int i = 0; i < p_testCount; ++i)
		{
			BatchBmpTest* pCurrTest = p_ppTests[i];

			pCurrTest->init(p_bitmap);
			passed = passed && pCurrTest->perform();

			if(!passed)
			{
				std::cout << "Test FAILED." << std::endl << std::endl;
				break;
			}else
			{
				std::cout << "Test passed." << std::endl << std::endl;
			}
		}

		return passed;
	}


	bool AccessPosTest::perform()
	{
		std::cout << "Testing on accessors of current position." << std::endl;

		bmp::AbsoluteCoordinate abs(*pBitmap);
		abs.set(10, 12);

		if(!pBitmap->setCurrentPos(abs))
		{
			std::cout << "Setting current position failed." << std::endl;
			return false;
		}

		if(!abs.equals( pBitmap->getCurrentPos() ))
		{
			std::cout << "Got a different coordinate than set." << std::endl;
			return false;
		}

		return true;
	}

	bool AccessColorTest::perform()
	{
		std::cout << "Testing on accessors of current color." << std::endl;

		bmp::Color24 color = {1, 42, 21};

		pBitmap->setCurrentColor(color);
		bmp::Color24 color2 = pBitmap->getCurrentColor();

		if(!color2.equals( color ))
		{
			std::cout << "Got a different color than set." << std::endl;
			return false;
		}

		return true;
	}

	bool AbsCoordCompatTest::perform()
	{
		std::cout << "Testing on (in)compatibility of absolute coordinates." << std::endl;

		bmp::BatchBitmap24 secondBitmap(15, 15);

		bmp::AbsoluteCoordinate absFirst(*pBitmap);

		if(secondBitmap.setCurrentPos(absFirst))
		{
			std::cout << "Absolute coordinates shall NOT be compatible (between two different bitmaps), test FAILED." << std::endl;
			return false;
		}

		return true;
	}
}
