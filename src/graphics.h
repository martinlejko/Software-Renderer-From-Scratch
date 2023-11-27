//
// Created by Martin Lejko on 22/11/2023.
//
#ifndef SRC_GRAPHICS_H
#define SRC_GRAPHICS_H
#include "tgaimage.h"
#include "datatypes.h"

void drawLine(const Point2D& p1, const Point2D& p2, const TGAColor& color, TGAImage& image);
void drawTriangle(const Point2D& p1, const Point2D& p2, const Point2D& p3, TGAImage& image);
bool isFlatOrLeftEdge(const Point2D& p1, const Point2D& p2);
void sortPointsClockwise(Point2D& p1, Point2D& p2, Point2D& p3);
#endif //SRC_GRAPHICS_H
