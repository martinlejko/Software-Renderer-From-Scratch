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
    int vertexIndex = 1;
    int faceIndex = 1;
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
            std::vector<FaceElement> face;
            FaceElement faceElement;
            while (iss >> faceElement.vertexIndex) {
                char separator;
                if (iss.peek() == '/') {
                    iss >> separator >> faceElement.textureIndex;
                    if (iss.peek() == '/') {
                        iss >> separator >> faceElement.normalIndex;
                    } else {
                        faceElement.normalIndex = 0; // Default value if not provided
                    }
                } else {
                    faceElement.textureIndex = 0; // Default value if not provided
                    faceElement.normalIndex = 0; // Default value if not provided
                }
                face.push_back(faceElement);
            }
            faces[faceIndex] = face;
            faceIndex++;
        }
    }

}

void Model::projectVerts(const int width, const int height) {
    for (auto& vert : verts) {
        Point3D point = vert.second;

        // Simple 2D projection without considering Z-coordinate
        int xProj = (point.x + 1.) * width / 2.;
        int yProj = (point.y + 1.) * height / 2.;

        projectedVerts[vert.first] = {xProj, yProj};
    }
}



void Model::drawModel(TGAImage &image, const int width, const int height) {
    TGAColor white = TGAColor(255, 255, 255, 255);
    projectVerts(width, height);
    for (const auto& face : faces) {
        Point2D p1 = projectedVerts[face.second[0].vertexIndex];
        Point2D p2 = projectedVerts[face.second[1].vertexIndex];
        Point2D p3 = projectedVerts[face.second[2].vertexIndex];
//        std::cout<< "Drawing triangle with vertices: (" << p1.x << ", " << p1.y << "), (" << p2.x << ", " << p2.y << "), (" << p3.x << ", " << p3.y << ")" << std::endl;
        drawLine(p1, p2, white, image);
        drawLine(p2, p3, white, image);
        drawLine(p3, p1, white, image);
    }

}


void Model::printVerticesAndFaces() {
    std::cout << "Vertices:" << std::endl;
    for (const auto& vertex : verts) {
        std::cout << "Vertex Index: " << vertex.first << " | Coordinates: (" << vertex.second.x << ", " << vertex.second.y << ", " << vertex.second.z << ")" << std::endl;
    }

    std::cout << "\nFaces:" << std::endl;
    for (const auto& face : faces) {
        std::cout << "Face Index: " << face.first << std::endl;
        for (const auto& faceElement : face.second) {
            std::cout << "  Vertex Index: " << faceElement.vertexIndex << " | Texture Index: " << faceElement.textureIndex << " | Normal Index: " << faceElement.normalIndex << std::endl;
        }
    }
}