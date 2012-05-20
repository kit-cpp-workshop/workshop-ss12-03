/*
 * polygon.cpp
 *
 *  Created on: 20.05.2012
 *      Author: markus
 */

#include "polygon.h"

namespace bmp {

    static RelativeCoordinate * copyToPolyline(RelativeCoordinate * const corners, const unsigned int numCorners);

    polygon::polygon(RelativeCoordinate * const corners, const unsigned int numCorners) :
        polyline(copyToPolyline(corners, numCorners), (numCorners > 0) ? numCorners + 1 : 0) {

        // assert (numCorners == 0) || (numCorners > 0) && (corners != null))
    }

    polygon::~polygon() {
        delete[] coords;
    }

    static RelativeCoordinate * copyToPolyline(RelativeCoordinate * const corners, const unsigned int numCorners) {
        if (numCorners == 0) {
            return NULL; // corner case, haha
        }

        RelativeCoordinate * const result = new RelativeCoordinate[numCorners + 1];

        for (unsigned int i = 0; i < numCorners; i++) {
            result[i] = corners[i];
        }

        result[numCorners] = corners[0];

        return result;
    }

} /* namespace bmp */
