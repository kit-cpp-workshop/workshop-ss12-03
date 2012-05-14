#include "line.h"
#include <cmath>


namespace bmp {
    bool line::draw(Bitmap24 &p_target, AbsoluteCoordinate p_from, AbsoluteCoordinate p_to, Color24 p_color) {
        if (!p_from.refersTo(p_target) || !p_to.refersTo(p_target)) {
            return false;
        }

        const int deltaX = p_to.getX() - p_from.getX();
        const int deltaY = p_to.getY() - p_from.getY();

        const int incX = p_to.getX() > p_from.getX() ? 1 : -1;
        const int incY = p_to.getY() > p_from.getY() ? 1 : -1;

        signed long err = 0;
        unsigned int x = p_from.getX();
        unsigned int y = p_from.getY();

        for (;;) {
            p_target.setPixel(x, y, p_color); // assert true

            if (x == p_to.getX()) {
                break;
            }

            signed long errX = err + 2 * deltaY * incX;
            signed long errY = err - 2 * deltaX * incY;

            if (std::abs(errX) <= std::abs(errY)) {
                x += incX;
                err = errX;
            } else {
                err = errY;
                y += incY;
            }
        }

        return true;
    }


	lineto::lineto(bmp::RelativeCoordinate p_to) : to( p_to ) {
	}

	lineto::~lineto() {
	}

	bool lineto::applyTo(bmp::BatchBitmap24 &p) {
		line lineObj;
		AbsoluteCoordinate absTo = to.convert(p);

		if(!lineObj.draw(p, p.getCurrentPos(), absTo, p.getCurrentColor())) {
			return false;
		}

		return p.setCurrentPos(absTo);
	}
}
