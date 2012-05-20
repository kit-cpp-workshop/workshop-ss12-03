/*
 * polygon.h
 *
 *  Created on: 20.05.2012
 *      Author: markus
 */

#ifndef POLYGON_H_
#define POLYGON_H_

#include "polyline.h"

namespace bmp {

    class polygon : public bmp::polyline {
        public:
            polygon(RelativeCoordinate * const corners, const unsigned int numCorners);
            virtual ~polygon();
    };

} /* namespace bmp */
#endif /* POLYGON_H_ */
