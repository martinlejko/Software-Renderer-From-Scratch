//
// Created by Martin Lejko on 23/11/2023.
//

#ifndef SRC_MODEL_H
#define SRC_MODEL_H
#include "datatypes.h"
#include "tgaimage.h"
#include <unordered_map>
#include <vector>

class Model {
public:
    Model(const char *filename);
    ~Model();
    int nverts() const;
    int nfaces() const;
    Point3D vert(int i);
    void drawModel(TGAImage &image, const int width, const int height);
    void printVerticesAndFaces();
private:
    std::unordered_map<int, Point3D> verts;
    std::unordered_map<int, Point2D> projectedVerts;
    std::unordered_map<int, std::vector<FaceElement>> faces;
    void parseModelFile(const char *filename);
    void projectVerts(const int width, const int height);
};
#endif //SRC_MODEL_H
