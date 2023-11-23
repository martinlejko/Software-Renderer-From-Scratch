//
// Created by Martin Lejko on 23/11/2023.
//

#ifndef SRC_MODEL_H
#define SRC_MODEL_H
#include "datatypes.h"
#include <unordered_map>
#include <vector>

class Model {
public:
    Model(const char *filename);
    ~Model();
    int nverts() const;
    int nfaces() const;
    Point3D vert(int i);

private:
    std::unordered_map<int, Point3D> verts;
    std::vector<std::vector<int>> faces;
    void parseModelFile(const char *filename);
};
#endif //SRC_MODEL_H
