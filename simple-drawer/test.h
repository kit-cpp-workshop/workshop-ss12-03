#include "batchbmp.h"


namespace bmp
{
	class Test
	{
	public:
		virtual ~Test() {}

		// pure virtual function which performs the test
		// returns whether the test has passed or not
		virtual bool perform() = 0;
	};


	class BatchBmpTest
		: public Test
	{
	public:
		BatchBmpTest()
			: pBitmap(0)
		{}

		virtual ~BatchBmpTest() {}

		virtual void init(BatchBitmap24& p_bitmap)
		{
			pBitmap = &p_bitmap;
		}


	protected:
		BatchBitmap24* pBitmap;
	};


	// initializes all tests with the bitmap and performs them
	// returns whether ALL tests have passed (true) or at least one failed (false)
	bool performTests(BatchBitmap24& p_bitmap, BatchBmpTest** p_ppTests, unsigned int p_testCount);


	class AccessPosTest
		: public BatchBmpTest
	{
		virtual bool perform();
	};
	class AccessColorTest
		: public BatchBmpTest
	{
		virtual bool perform();
	};

	class AbsCoordCompatTest
		: public BatchBmpTest
	{
		virtual bool perform();
	};
}
