#include "tgaimage.h"
#include "graphics.h"
#include "datatypes.h"
#include "model.h"
#include <iostream>

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);

int main(int argc, char** argv) {
    int width = 2500;
    int height = 2500;
    TGAImage image(width, height, TGAImage::RGB);
    Model africanHead("/Users/martinlejko/Desktop/github/Software-Renderer-From-Scratch/src/objects/african_head.obj");
    africanHead.drawModel(image, width, height);
    std::cout << "Number of vertices: " << africanHead.nverts() << std::endl;
    std::cout << "Number of faces: " << africanHead.nfaces() << std::endl;
    image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
    image.write_tga_file("output.tga");
    return 0;
}

