//
// Created by Martin Lejko on 23/11/2023.
//
#include "model.h"
#include "datatypes.h"
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
