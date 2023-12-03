//
// Created by Martin Lejko on 23/11/2023.
//

#ifndef SRC_DATATYPES_H
#define SRC_DATATYPES_H
struct Point2D {
    int x;
    int y;
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

struct Vector3D {
    float x;
    float y;
    float z;

    Vector3D(float xVal = 0, float yVal = 0, float zVal = 0) : x(xVal), y(yVal), z(zVal) {}
    Vector3D(const Point3D& p1, const Point3D& p2) : x(p2.x - p1.x), y(p2.y - p1.y), z(p2.z - p1.z) {}

    Vector3D crossProduct(const Vector3D& v) const;
    double dotProduct(const Vector3D& v) const ;
};


struct FaceElement {
    int vertexIndex;
    int textureIndex;
    int normalIndex;
};
#endif //SRC_DATATYPES_H
