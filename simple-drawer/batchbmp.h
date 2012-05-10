#ifndef H_BATCHBITMAP24
#define H_BATCHBITMAP24




#include <istream>
#include <utility>
#include "bmp.h"


namespace bmp
{
	class AbsoluteCoordinate;
	class RelativeCoordinate;
	class BatchBitmap24;
}

// magic for reading from command line / file, don't care
std::istream& operator >>(std::istream& p_o, bmp::RelativeCoordinate& p_c);


namespace bmp
{
	// A class for representing an absolute coordinate (what you would call "Coordinate")
	class AbsoluteCoordinate
	{
		// INVARIANT: the x and y part are valid (within the boundaries of the bitmap referring to)


	public:
		// we need to store the bitmap, which the coordinate is referring to, internally
		// to preserve the invariant
		AbsoluteCoordinate(Bitmap24& p_ref);


		// set the coordinate, preserves the invariant
		// returns false in case of error (p_x or p_y not in bitmap range)
		bool set(unsigned int p_x, unsigned int p_y);

		// getters
		unsigned int getX();
		unsigned int getY();

		// convert to a relative coordinate
		RelativeCoordinate convert();


	private:
		friend class BatchBitmap24;
		Bitmap24* refBitmap;

		unsigned int x;
		unsigned int y;
	};




	class RelativeCoordinate
	{
		// INVARIANT: x and y are in [0, 1]


	public:
		RelativeCoordinate();

		// returns false in case of error (p_x or p_y not in [0, 1])
		bool set(double p_x, double p_y);

		// set the coordinate, preserves the invariant
		// getters
		double getX();
		double getY();

		AbsoluteCoordinate convert(BatchBitmap24& p_ref);


	private:
		double x;
		double y;
	};




	// a bitmap plus a current color and a current position
	class BatchBitmap24
		: public Bitmap24
	{
	public:
		BatchBitmap24(unsigned int p_width, unsigned int p_height);
		virtual ~BatchBitmap24();

		// we will overload getPixel and setPixel with Coordinate-versions,
		// so we need to explicitly introduce the base class versions here
		// (otherwise they would be hidden by the versions here)
		using Bitmap24::getPixel;
		using Bitmap24::setPixel;

		// the batch bitmap class allows the use of an AbsoluteCoordinate
		// returns false in case of error (coordinate does not refer to this bitmap)
		bool getPixel(AbsoluteCoordinate p_coord, /*out*/ Color24& p_color);
		bool setPixel(AbsoluteCoordinate p_coord, /*in */ Color24  p_color);


		// accessors for the current position
		void setCurrentPos(AbsoluteCoordinate p);
		AbsoluteCoordinate getCurrentPos();

		// accessors for the current color
		Color24 getCurrentColor();
		void setCurrentColor(Color24 c);


	private:
		AbsoluteCoordinate currentPos;
		Color24 currentColor;
	};
}




#endif
