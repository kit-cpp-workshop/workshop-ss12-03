#include "batchbmp.h"
#include "line.h"
#include "fill.h"

#include <iostream>

int main() {
    bmp::BatchBitmap24 blackBitmap(100, 100);

    bmp::Color24 blue = { 0, 0, 255 };
    bmp::Color24 black = { 0, 0, 0 };

    /*
    for (unsigned int iRow = 0; iRow < blackBitmap.getHeight(); ++iRow) {
        for (unsigned int iColumn = 0; iColumn < blackBitmap.getWidth(); ++iColumn) {
            blackBitmap.setPixel(iColumn, iRow, blue);
        }
    }*/

    blackBitmap.setCurrentColor(blue);

    bmp::fill().applyTo(blackBitmap);

    blackBitmap.setCurrentColor(black);

    bmp::AbsoluteCoordinate end1(blackBitmap);
    bmp::AbsoluteCoordinate end2(blackBitmap);
    bmp::AbsoluteCoordinate end3(blackBitmap);
    bmp::AbsoluteCoordinate end4(blackBitmap);

    if (!end1.set(90, 50) & !end2.set(30, 70) & !end3.set(5, 30) & !end4.set(99, 0)) {
        std::cout << "error!" << std::endl;
    } else {
        bmp::lineto(end1.convert()).applyTo(blackBitmap);
        bmp::lineto(end2.convert()).applyTo(blackBitmap);
        bmp::lineto(end3.convert()).applyTo(blackBitmap);
        bmp::lineto(end4.convert()).applyTo(blackBitmap);
    }

    blackBitmap.save("foo.bmp");

    return 0;
}

