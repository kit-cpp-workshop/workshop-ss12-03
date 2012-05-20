/*
 * fill.cpp
 *
 *  Created on: 16.05.2012
 *      Author: markus
 */

#include "fill.h"

namespace bmp {

    void filler::fillBitmap(Bitmap24 &bitmap, Color24 color) {
        for (unsigned int y = 0; y < bitmap.getHeight(); y++) {
             for (unsigned int x = 0; x < bitmap.getWidth(); x++) {
                bitmap.setPixel(x, y, color); // assert result == true
            }
        }
    }

    fill::~fill() {
    }

    bool fill::applyTo(BatchBitmap24 &p) {
        filler().fillBitmap(p, p.getCurrentColor());

        return true;
    }

} /* namespace bmp */
