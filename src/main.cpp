#include "tgaimage.h"
#include "graphics.h"
#include "datatypes.h"
#include "model.h"
#include <iostream>

int main(int argc, char** argv) {
    int width = 2500;
    int height = 2500;
    TGAImage image(width, height, TGAImage::RGB);

    Model africanHead("/Users/martinlejko/Desktop/github/Software-Renderer-From-Scratch/src/objects/african_head.obj");
    africanHead.drawModel(image, width, height);
//    Point2D p2 = {400, 1500};
//    Point2D p1 = {1000, 500};
//    Point2D p3 = {300, 800};
//    drawTriangle(p1,p2, p3, image);

    image.flip_vertically(); // I want to have the origin at the left bottom corner of the image
    image.write_tga_file("output.tga");
    return 0;
}

