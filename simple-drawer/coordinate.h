#ifndef COORDINATE_H
#define COORDINATE_H

// not required, since we only use pointers and refs in this header
#include "bmp.h"


namespace bmp
{
	// so-called "forward declarations", see Addendum: Headers for Workshop 03
	class AbsoluteCoordinate;
	class RelativeCoordinate;


	/**
	 * Stores a valid coordinate of a specific bitmap canvas
	 *
	 * A value-pair x, y is stored, referring to a concrete (and well-defined)
	 * pixel. An instance of AbsoluteCoordinate is bound to a specific canvas
	 * (a Bitmap24 instance), so that it cannot contain in invalid coordinate.
	* The coordinate has to be in the valid range (0, 0) to (width-1, height-1)
	* with respect to the dimensions of the canvas referred to.
	 * Because the coordinate is bound to a specific canvas, you cannot use an
	* instance of AbsoluteCoordinate for two different canvases (even if they
	* have the same size).
	 
	 * You can use set(), getX() and getY() to access the x- and y-component
	 * of the coordinate.
	 *
	 * @invariant the x and y part are valid within the boundaries of the bitmap
	 * canvas referring to
	 */
	class AbsoluteCoordinate
	{
	public:
		/**
		 * Creates a AbsoluteCoordinate referring to the Bitmap24 instance
		 * passed.
		 *
		 * NOTE: you can also pass instances of classes derived (publicly)
		 * from Bitmap24, such as BatchBitmap24
		 *
		 * @param p_ref the bitmap canvas instance this AbsoluteCoordinate shall
		 * refer to
		 */
		AbsoluteCoordinate(Bitmap24& p_ref);

		/**
		 * Sets the coordinate values of this instance to the passed values.
		 * Invalid coordinates will be ignored, the return value indicates if
		 * the values have been accepted or not.
		 *
		 * @param p_x the X coordinate component, with 0 <= p_x <= width - 1
		 * @param p_y the Y coordinate component, with 0 <= p_y <= height - 1
		 * @return true if the passed values are within the valid value range,
		 *         else false
		 */
		bool set(unsigned int p_x, unsigned int p_y);

		/**
		 * Returns the value of the X coordinate component.
		 *
		 * @return the X coordinate value
		 */
		unsigned int getX();
		/**
		 * Returns the value of the Y coordinate component.
		 *
		 * @return the Y coordinate value
		 */
		unsigned int getY();

		/**
		 * Creates a RelativeCoordinate instance which represents the same
		 * position as this AbsoluteCoordinate instance
		 *
		 * This function returns a new RelativeCoordinate, which refers to the
		 * same position (coordinate) as does this AbsoluteCoordinate instance.
		 *
		 * NOTE: the RelativeCoordinate might not be precise enough to hold the
		 * following identity, yet it will hold on common compilers & PCs:
		 * AbsoluteCoordinate a(myCanvas);
		 * a.convert().convert(myCanvas).equals(a)
		 *
		 * @return the x component
		 */
		RelativeCoordinate convert();

		/**
		 * Indicates if the passed Bitmap24 instance equals the one to which
		 * this AbsoluteCoordinate refers.
		 *
		 * @param p the Bitmap24 to check
		 * @return true if this AbsoluteCoordinate refers to the passed Bitmap24,
		 *         else false
		 */
		bool refersTo(Bitmap24& p);

		/**
		 * Check if two absoluteCoordinate instances are equal.
		 *
		 * NOTE: it also checks the bitmap canvas referred to
		 *
		 * @return true if both coordinates refer to the same bitmap canvas
		 *         instance AND both x- and y-components are equal
		 */
		bool equals(AbsoluteCoordinate p);


	private:
		/**
		 * The Bitmap24 to which this AbsoluteCoordinate refers.
		 */
		Bitmap24* refBitmap;

		/**
		 * The absolute X coordinate value.
		 */
		unsigned int x;
        /**
         * The absolute Y coordinate value.
         */
		unsigned int y;
	};




	/**
	 * Stores a valid coordinate independent from a bitmap canvas instance.
	 *
	 * The RelativeCoordinate stores a position relative to the size of a
	 * bitmap canvas, that is, a fraction of the size.
	 * The X- and y-component therefore are in [0, 1] (including 1, but that's
	 * a special case).
	 * 
	 * You can use set(), getX() and getY() to access the X- and y-component
	 * of the coordinate.
	 * 
	 * NOTE: A RelativeCoordinate does not necessarily have a well-defined
	 * relationship to a single pixel, but on common compilers & PCs it's
	 * even more precise.
	 *
	 * @invariant the X and Y part are in [0, 1]
	 */
	class RelativeCoordinate
	{
	public:
		/**
		 * Creates a instance of RelativeCoordinate referring to (0, 0).
		 *
		 * The X- and Y-component are zero-intialized, so the create coordinate
		 * initially refers to the point (0, 0).
		 */
		RelativeCoordinate();

		/**
		 * Sets the coordinate components.
		 * The components have to be in [0, 1].
		 *
		 * @param p_x the new X coordinate component to be set
		 * @param p_y the new Y coordinate component to be set
		 * @return false in case of error (p_x or p_y not in [0, 1])
		 */
		// returns false in case of error (p_x or p_y not in [0, 1])
		/**
		 * Sets the coordinate values of this instance to the passed values.
         * Invalid coordinates will be ignored, the return value indicates if
         * the values have been accepted or not.
		 *
		 * @param p_x the X coordinate component, with 0 <= p_x <= 1
		 * @param p_y the Y coordinate component, with 0 <= p_y <= 1
		 * @return true if the passed values are within the valid value range,
		 *         else false
		 */
		bool set(double p_x, double p_y);

		/**
		 * Returns the value of the X coordinate component.
		 *
		 * @return the X coordinate component
		 */
		double getX();
		/**
		 * Returns the value of the Y coordinate component.
		 *
		 * @return the Y coordinate component
		 */
		double getY();

		/**
		 * Creates an AbsoluteCoordinate instance which represents the same
		 * position on the bitmap canvas passed.
		 *
		 * @param p_ref the bitmap canvas used as reference for the
		 *              conversion to absolute coordinate values
		 * @return the AbsoluteCoordinate instance representing this
		 *         RelativeCoordinates on the passed bitmap canvas
		 */
		AbsoluteCoordinate convert(Bitmap24& p_ref);

        /**
         * Compares the passed RelativeCoordinate against this instance.
         *
         * @param p the instance to compare with
         * @return true if this instance is equal to the passed one, else false
         */
		bool equals(RelativeCoordinate p);


	private:
		/**
		 * The relative X coordinate value. 0 <= x <= 1
		 */
		double x;
		/**
		 * The absolute Y coordinate value. 0 <= y <= 1
		 */
		double y;
	};

	// magic for reading from command line / file, don't care
	std::istream& operator >>(std::istream& p_o, bmp::RelativeCoordinate& p_c);
}

#endif
