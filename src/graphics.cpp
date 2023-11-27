//
// Created by Martin Lejko on 22/11/2023.
//
#include "tgaimage.h"
#include "graphics.h"
#include "datatypes.h"
#include <algorithm>
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

bool isFlatOrLeftEdge(const Point2D& p1, const Point2D& p2) {
    //check if the triangle has flat or left edge
    Vector2D edge = Vector2D(p1, p2);
    bool isFlatEdge = edge.y == 0 && edge.x > 0;
    bool isLeftEdge = edge.y < 0;
    return isFlatEdge || isLeftEdge;
}

void sortPointsClockwise(Point2D p1, Point2D p2, Point2D p3) {
    if (p1.y > p2.y) {
        Point2D temp = p1;
        p1 = p2;
        p2 = temp;
    }
    if (p1.y > p3.y) {
        Point2D temp = p1;
        p1 = p3;
        p3 = temp;
    }
    if (p2.y > p3.y) {
        Point2D temp = p2;
        p2 = p3;
        p3 = temp;
    }
}


void drawTriangle(const Point2D& p1, const Point2D& p2, const Point2D& p3, TGAImage& image) {
    //sort the points in clockwise order
    sortPointsClockwise(p1, p2, p3);
    std::vector<std::vector<float>> pointColors = {{255, 0, 0, 255}, {0, 255, 0, 255}, {0, 0, 255, 255}};

    //find the bounding box of the triangle
    int minX = std::min(p1.x, std::min(p2.x, p3.x));
    int minY = std::min(p1.y, std::min(p2.y, p3.y));
    int maxX = std::max(p1.x, std::max(p2.x, p3.x));
    int maxY = std::max(p1.y, std::max(p2.y, p3.y));

    //calculate the deltas for row and column steps
    int deltaColAB = p2.y - p3.y;
    int deltaColBC = p3.y - p1.y;
    int deltaColCA = p1.y - p2.y;

    int deltaRowAB = p3.x - p2.x;
    int deltaRowBC = p1.x - p3.x;
    int deltaRowCA = p2.x - p1.x;

    //once per triangle, calculate the bias for each edge of the triangle
    int bias1 = isFlatOrLeftEdge(p2, p3) ? 0 : -1;
    int bias2 = isFlatOrLeftEdge(p3, p1) ? 0 : -1;
    int bias3 = isFlatOrLeftEdge(p1, p2) ? 0 : -1;

    //inicitialize the frist pixel and vectors of the triangle
    Point2D firstPixel = {minX, minY};
    Vector2D AB(p2, p3);
    Vector2D BC(p3, p1);
    Vector2D CA(p1, p2);

    //calculate the cross product for the first pixel
    int crossProductAbPRow = AB.crossProduct(Vector2D(p2, firstPixel)) + bias1;
    int crossProductBcPRow = BC.crossProduct(Vector2D(p3, firstPixel)) + bias2;
    int crossProductCaPRow= CA.crossProduct(Vector2D(p1, firstPixel)) + bias3;

    float area = static_cast<float>(Vector2D(p1, p2).crossProduct(Vector2D(p1, p3)));

    //iterate over the bounding box and color the pixels inside the triangle
    for (int y = minY; y <= maxY; y++) {
        int crossProductAB_p = crossProductAbPRow;
        int crossProductBC_p = crossProductBcPRow;
        int crossProductCA_p = crossProductCaPRow;
        for (int x = minX; x <= maxX; x++) {
            //check if the pixel is inside the triangle
            bool isInsideTriangle = (crossProductAB_p >= 0 && crossProductBC_p >= 0 && crossProductCA_p >= 0 );

            if (isInsideTriangle) {
                //calculate the barycentric coordinates
                float alpha = static_cast<float>(crossProductAB_p) / area;
                float beta = static_cast<float>(crossProductBC_p) / area;
                float gamma = static_cast<float>(crossProductCA_p) / area;

                int r = static_cast<int>(pointColors[0][0] * alpha + pointColors[1][0] * beta + pointColors[2][0] * gamma);
                int g =  static_cast<int>(pointColors[0][1] * alpha +  pointColors[1][1] * beta +  pointColors[2][1] * gamma);
                int b =  static_cast<int>(pointColors[0][2] * alpha +  pointColors[1][2] * beta + pointColors[2][2] * gamma);
                TGAColor color = TGAColor(r, g, b, 255);
                image.set(x, y, color);
            }
            crossProductAB_p += deltaColAB;
            crossProductBC_p += deltaColBC;
            crossProductCA_p += deltaColCA;
        }
        crossProductAbPRow += deltaRowAB;
        crossProductBcPRow += deltaRowBC;
        crossProductCaPRow += deltaRowCA;
    }
}

