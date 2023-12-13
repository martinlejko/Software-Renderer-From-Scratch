#include "tgaimage.h"
#include "graphics.h"
#include "datatypes.h"
#include "model.h"
#include <iostream>

int main() {
    int width = 1200;
    int height = 1200;
    Vector3D lightDirection(0, 0, -1);


    TGAImage image(width, height, TGAImage::RGB);
    TGAImage img(width, height, TGAImage::RGB);
    Model africanHead("/Users/martinlejko/Desktop/github/Software-Renderer-From-Scratch/src/objects/african_head.obj");
    africanHead.loadTexture(img);
    africanHead.drawModelWithLight(image, img, width, height, lightDirection);


    image.flip_vertically(); // I want to have the origin at the left bottom corner of the image
    image.write_tga_file("output.tga");
    return 0;
}

