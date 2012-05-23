#ifndef COORDINATE_H
#define COORDINATE_H

// not required, since we only use pointers and refs in this header
#include "bmp.h"


namespace bmp
{
	class AbsoluteCoordinate;
	class RelativeCoordinate;


	// A class for representing an absolute coordinate (what you would call "Coordinate")
	/**
	 * This class represents two dimensional (pixel) coordinates linked to a
	 * Bitmap24 instance.
	 *
	 * Invariant: An AbsoluteCoordinate instance permits/stores only coordinate
	 * values which are within the boundaries of the Bitmap24 to which it refers.
	 * The valid value range starts at (0, 0) and ends at
     * (width - 1, height - 1) where width and height are the dimensions
     * of the Bitmap24 linked to.
	 */
	class AbsoluteCoordinate
	{
		// INVARIANT: the x and y part are valid (within the boundaries of the bitmap referring to)


	public:
	    /**
	     * Creates a new AbsoluteCoordinate instance and sets up the linkage to
	     * the passed Bitmap24.
	     *
	     * @param p_ref the Bitmap24 to link against
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
		 * Creates a RelativeCoordinate which represents the same position like
		 * this AbsoluteCoordinate instance, if applied to the same Bitmap24.
		 *
		 * @return a RelativeCoordinate representing this AbsoluteCoordinate on
		 *         the linked Bitmap24
		 */
		RelativeCoordinate convert();

		// returns true if &p == refBitmap
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
		 * Compares the passed AbsoluteCoordinate against this instance.
		 *
		 * @param p the instance to compare with
		 * @return true if this instance is equal to the passed one, else false
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
	 * This class implements two dimensional (pixel) coordinates on an abstract
	 * plane with a value range from (0, 0) to (1, 1).
	 */
	class RelativeCoordinate
	{
		// INVARIANT: x and y are in [0, 1]


	public:
        /**
         * Creates a new RelativeCoordinate instance with value (0, 0).
         */
		RelativeCoordinate();

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
		 * position on the Bitmap24 it refers to.
		 *
		 * @param p_ref the Bitmap24 used as reference for the conversion to
		 *              absolute coordinate values
		 * @return the AbsoluteCoordinate instance representing this
		 *         RelativeCoordinates on the passed Bitmap24
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
