//
// Created by Martin Lejko on 23/11/2023.
//

#ifndef SRC_DATATYPES_H
#define SRC_DATATYPES_H
struct Point2D {
    int x;
    
};

struct Point3D {
    float x;
    float y;
    float z;
};

struct Vector2D {
    int x;
    int y;

    Vector2D(int xVal = 0, int yVal = 0) : x(xVal), y(yVal) {}
    Vector2D(const Point2D& p1, const Point2D& p2) : x(p2.x - p1.x), y(p2.y - p1.y) {}

    int crossProduct(const Vector2D& v) const;
};


struct FaceElement {
    int vertexIndex;
    int textureIndex;
    int normalIndex;
};
#endif //SRC_DATATYPES_H
