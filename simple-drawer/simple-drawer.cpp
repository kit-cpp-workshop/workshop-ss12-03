#include "batchbmp.h"
#include "line.h"
#include "fill.h"
#include "polygon.h"

#include <iostream>

static bmp::Color24 green = { 0, 255, 0 };
static bmp::Color24 blue = { 0, 0, 255 };
static bmp::Color24 black = { 0, 0, 0 };

static void drawSchroedingersCat(bmp::BatchBitmap24 &bm);

int main() {
    bmp::BatchBitmap24 blackBitmap(100, 100);

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

    blackBitmap.setCurrentColor(black);
    bmp::fill().applyTo(blackBitmap);
    blackBitmap.setCurrentColor(green);
    drawSchroedingersCat(blackBitmap);
    blackBitmap.save("schroedinger.bmp");

    return 0;
}

void drawSchroedingersCat(bmp::BatchBitmap24 &bm) {
    bmp::RelativeCoordinate corners[4];

    corners[0].set(0.25, 0.25);
    corners[1].set(0.25, 0.75);
    corners[2].set(0.75, 0.75);
    corners[3].set(0.75, 0.25);

    bmp::polygon(corners, 4).applyTo(bm); // schroedingers cat lives here
}
