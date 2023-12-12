//
// Created by Martin Lejko on 25/11/2023.
//
#include "datatypes.h"
#include <cmath>
int Vector2D::crossProduct(const Vector2D& v) const {
    return x * v.y - y * v.x;
}

Vector3D Vector3D::crossProduct(const Vector3D& v) const {
    return {y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x};
}

double Vector3D::dotProduct(const Vector3D& v) const {
    return x * v.x + y * v.y + z * v.z;
}

float Vector3D::magnitude() {
    return sqrt(x * x + y * y + z * z);
}

void Vector3D::normalize() {
    float magnitude = this->magnitude();
    x /= magnitude;
    y /= magnitude;
    z /= magnitude;
}