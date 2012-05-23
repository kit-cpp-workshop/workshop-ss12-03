#include <istream>

// not required, since we only use pointers and refs in this header
#include "bmp.h"


namespace bmp
{
	class AbsoluteCoordinate;
	class RelativeCoordinate;


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

		// returns true if &p == refBitmap
		bool refersTo(Bitmap24& p);

		bool equals(AbsoluteCoordinate p);


	private:
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

		// convert to an absolute coordinate
		AbsoluteCoordinate convert(Bitmap24& p_ref);

		bool equals(RelativeCoordinate p);


	private:
		double x;
		double y;
	};

	// magic for reading from command line / file, don't care
	std::istream& operator >>(std::istream& p_o, bmp::RelativeCoordinate& p_c);
}
