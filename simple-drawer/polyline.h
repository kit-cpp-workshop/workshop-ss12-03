/*
 * polyline.h
 *
 *  Created on: 16.05.2012
 *      Author: markus
 */

#ifndef POLYLINE_H_
#define POLYLINE_H_

#include "coordinate.h"
#include "drawable.h"

namespace bmp {

    class polyline : IBatchDrawable {
        public:
            polyline(RelativeCoordinate * const coords, const unsigned int numCoords);
            virtual ~polyline();

            virtual bool applyTo(BatchBitmap24& p_target);
        private:
            RelativeCoordinate * const coords;
            const unsigned int numCoords;
    };

} /* namespace bmp */
#endif /* POLYLINE_H_ */
