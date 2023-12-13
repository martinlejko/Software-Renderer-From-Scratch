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
    int nverts() const;
    int nfaces() const;
    void drawModel(TGAImage &image, int width, int height);
    void drawModelWithLight(TGAImage &image, TGAImage &texture, int width, int height, Vector3D lightDirection);
    void printVerticesAndFaces();
    void loadTexture(TGAImage &image);
private:
    std::unordered_map<int, Point3D> verts;
    std::unordered_map<int, Point2D> projectedVerts;
    std::unordered_map<int, std::vector<FaceElement>> faces;
    void parseModelFile(const char *filename);
    void projectVerts(int width, int height);
};
#endif //SRC_MODEL_H
