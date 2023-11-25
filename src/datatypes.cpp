//
// Created by Martin Lejko on 25/11/2023.
//
#include "datatypes.h"
int Vector2D::crossProduct(const Vector2D& v) const {
    return x * v.y - y * v.x;
}