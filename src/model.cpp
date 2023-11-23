//
// Created by Martin Lejko on 23/11/2023.
//
#include "model.h"
#include "datatypes.h"
#include "graphics.h"
#include <fstream>
#include <iostream>
#include <sstream>

Model::Model(const char* filename) {
    parseModelFile(filename);
}

Model::~Model() {
    verts.clear();
    faces.clear();
}

int Model::nverts() const {
    return verts.size();
}

int Model::nfaces() const {
    return faces.size();
}

void Model::parseModelFile(const char* filename){
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open or read the file " << filename << std::endl;
        return;
    }

    std::string line;
    int vertexIndex = 0;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string type;
        iss >> type;
        if (type == "v") {
            Point3D point;
            iss >> point.x >> point.y >> point.z;
            verts[vertexIndex] = point;
            vertexIndex++;
        } else if (type == "f") {
            std::vector<int> face;
            int idx;
            while (iss >> idx) {
                face.push_back(idx);
            }
            faces.push_back(face);
        }
    }
}

void Model::projectVerts(const int width, const int height) {
    for (auto& vert : verts) {
        Point3D point = vert.second;
        projectedVerts[vert.first] = {int((point.x + 1.) * width / 2. + .5), int((point.y + 1.) * height / 2. + .5)};
    }
}

void Model::drawModel(TGAImage &image, const int width, const int height) {
    projectVerts(width, height);

    for (auto& face : faces) {
        Point2D p1 = projectedVerts[face[0]];
        Point2D p2 = projectedVerts[face[1]];
        Point2D p3 = projectedVerts[face[2]];
    }

}