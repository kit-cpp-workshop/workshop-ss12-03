#ifndef H_BATCHBITMAP24
#define H_BATCHBITMAP24




#include <istream>
#include <utility>
#include "bmp.h"


namespace bmp
{
	class AbsoluteCoordinate
	{
	public:
		AbsoluteCoordinate(BatchBitmap24& p_ref);


		bool set(unsigned int p_x, unsigned int p_y);

		unsigned int getX();
		unsigned int getY();

		RelativeCoordinate convert();

		AbsoluteCoordinate& operator =(AbsoluteCoordinate p);


	private:
		BatchBitmap24& refBitmap;

		unsigned int x;
		unsigned int y;
	};




	class RelativeCoordinate
	{
	public:
		RelativeCoordinate(double p_x = 0, double p_y = 0);	// to enforce invariant

		bool set(double p_x, double p_y);

		double getX();
		double getY();

		AbsoluteCoordinate convert(BatchBitmap24& p_ref);


		friend std::istream& operator >>(std::istream& p_o, RelativeCoordinate& p_c)
		{
			bmp::RelativeCoordinate temp;
			p_o >> temp.x;
			p_o >> temp.y;

			if(p_o.good())
			{
				std::swap(p_c, temp);
			}

			return p_o;
		}


	private:
		double x;
		double y;
	};




	struct Color
	{
		uint8_t red;
		uint8_t green;
		uint8_t blue;

		Color(uint8_t p_red, uint8_t p_green, uint8_t p_blue)
			: red(p_red)
			, green(p_green)
			, blue(p_blue)
		{}
	};




	// a bitmap plus a current color and a current position
	class BatchBitmap24
		: public Bitmap24
	{
	public:
		BatchBitmap24();
		virtual ~BatchBitmap24();

		void setCurrentPos(RelativeCoordinate p);
		RelativeCoordinate getCurrentPos();
		void setCurrentPosAbs(AbsoluteCoordinate p);
		AbsoluteCoordinate getCurrentPosAbs();

		Pixel24 getPixel(AbsoluteCoordinate p);

		Color getCurrentColor();
		void setCurrentColor(Color c);


	private:
		AbsoluteCoordinate currentPos;
		Color currentColor;
	};
}




#endif
