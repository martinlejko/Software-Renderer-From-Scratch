//
// Created by Martin Lejko on 22/11/2023.
//
#include "tgaimage.h"
#include "graphics.h"
#include <iostream>

void drawLine(const Point2D& p1, const Point2D& p2, const TGAColor& color, TGAImage& image) {
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

void drawTriangle(const Point2D& p1, const Point2D& p2, const Point2D& p3, const TGAColor& color, TGAImage& image) {
    drawLine(p1, p2, color, image);
    drawLine(p2, p3, color, image);
    drawLine(p3, p1, color, image);
}