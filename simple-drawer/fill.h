/*
 * fill.h
 *
 *  Created on: 16.05.2012
 *      Author: markus
 */

#ifndef FILL_H_
#define FILL_H_

#include "bmp.h"
#include "batchbmp.h"
#include "drawable.h"

namespace bmp {

    class filler {
        public:
            void fillBitmap(Bitmap24 &bitmap, Color24 color);
    };

    class fill: IBatchDrawable {
        public:
            virtual ~fill();

            virtual bool applyTo(BatchBitmap24 &p);
    };

} /* namespace bmp */
#endif /* FILL_H_ */
