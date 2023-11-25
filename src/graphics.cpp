//
// Created by Martin Lejko on 22/11/2023.
//
#include "tgaimage.h"
#include "graphics.h"
#include <iostream>


void drawLine(const Point2D& p1, const Point2D& p2, const TGAColor& color, TGAImage& image) {
    //Bresenham's line algorithm
    int x = p1.x;
    int y = p1.y;
    int dx = abs(p2.x - p1.x);
    int dy = abs(p2.y - p1.y);
    int sx = p1.x < p2.x ? 1 : -1;
    int sy = p1.y < p2.y ? 1 : -1;
    int err = dx - dy;

    while (true) {
        //colors the pixel at (x, y) with the given color
        image.set(x, y, color);

        if (x == p2.x && y == p2.y) {
            break;
        }
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x += sx;
        }
        if (e2 < dx) {
            err += dx;
            y += sy;
        }
    }
}

//clockwide order
void drawTriangle(const Point2D& p1, const Point2D& p2, const Point2D& p3, const TGAColor& color, TGAImage& image) {
    //find the bounding box of the triangle
    int minX = std::min(p1.x, std::min(p2.x, p3.x));
    int minY = std::min(p1.y, std::min(p2.y, p3.y));
    int maxX = std::max(p1.x, std::max(p2.x, p3.x));
    int maxY = std::max(p1.y, std::max(p2.y, p3.y));

    //iterate over the bounding box and color the pixels inside the triangle
    for (int y = minY; y <= maxY; y++) {
        for (int x = minX; x <= maxX; x++) {
            Point2D p(x, y);
            //check if the pixel is inside the triangle
            if (isInsideTriangle(p, p1, p2, p3)) {
                image.set(x, y, color);
            }
        }
    }
}

bool isInsideTriangle(){
    //We use the cross product to declare if the point is inside the triangle, we use the clockwise order
    //For the 2D the cross product will be the z component of the 3D cross product
    
}