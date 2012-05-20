/*
 * polyline.cpp
 *
 *  Created on: 16.05.2012
 *      Author: markus
 */

#include "polyline.h"
#include "batchbmp.h"
#include "line.h"

namespace bmp {

    polyline::polyline(RelativeCoordinate * const coords, const unsigned int numCoords) :
            coords(coords),
            numCoords(numCoords) {
        // assert (numCoords == 0) || (numCords > 0) && (coords != null))
    }

    polyline::~polyline() {
    }

    bool polyline::applyTo(BatchBitmap24& p_target) {
        if (numCoords > 0) {
            p_target.setCurrentPos(coords[0].convert(p_target));
        }

        for (unsigned int i = 1; i < numCoords; i++) {
            lineto(coords[i]).applyTo(p_target);
        }

        return true;
    }

} /* namespace bmp */
