#include "tgaimage.h"
#include "graphics.h"
#include "datatypes.h"
#include "model.h"
#include <iostream>

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);

int main(int argc, char** argv) {
    TGAImage image(100, 100, TGAImage::RGB);
//  image.set(52, 41, red);
    Point2D pointA = {2, 1};
    Point2D pointB = {80, 50};
    Point2D pointC = {30, 80};
    Model africanHead("/Users/martinlejko/Desktop/github/Software-Renderer-From-Scratch/src/objects/african_head.obj");
    std::cout << "nverts: " << africanHead.nverts() << std::endl;
    std::cout << "nfaces: " << africanHead.nfaces() << std::endl;
    drawLine(pointA, pointB, red, image);
    drawTriangle(pointA, pointB, pointC, white, image);
    image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
    image.write_tga_file("output.tga");
    return 0;
}

