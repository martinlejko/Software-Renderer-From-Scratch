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

int Model::nverts() const {
    return static_cast<int>(verts.size());
}

int Model::nfaces() const {
    return static_cast<int>(faces.size());
}

void Model::printVerticesAndFaces() {
    std::cout << "Vertices:" << std::endl;
    for (const auto& vertex : verts) {
        std::cout << "Vertex Index: " << vertex.first << " | Coordinates: (" <<
                  vertex.second.x << ", " << vertex.second.y << ", " << vertex.second.z << ")" << std::endl;
    }

    std::cout << "\nFaces:" << std::endl;
    for (const auto& face : faces) {
        std::cout << "Face Index: " << face.first << std::endl;
        for (const auto& faceElement : face.second) {
            std::cout << "  Vertex Index: " << faceElement.vertexIndex << " | Texture Index: " <<
                      faceElement.textureIndex << " | Normal Index: " << faceElement.normalIndex << std::endl;
        }
    }
}

void Model::parseModelFile(const char* filename){
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open or read the file " << filename << std::endl;
        return;
    }

    std::string line;
    int vertexIndex = 1; // Starting from index 1 due to object file definition
    int faceIndex = 1;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string type;
        iss >> type;
        if (type == "v") {
            Point3D point{};
            iss >> point.x >> point.y >> point.z;
            verts[vertexIndex] = point;
            vertexIndex++;
        } else if (type == "f") {
            std::vector<FaceElement> face;
            FaceElement faceElement{};
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
        } else if (type == "vt") {
            continue;
        }
    }

}

void Model::loadTexture(TGAImage &image) {
    image.read_tga_file("/Users/martinlejko/Desktop/github/Software-Renderer-From-Scratch/src/objects/african_head_diffuse.tga");
    image.flip_vertically();
}

void Model::projectVerts(const int width, const int height) {
    for (auto& vert : verts) {
        Point3D point = vert.second;
        // Simple 2D projection without considering Z-coordinate
        // Static cast is used as the pixel coordinates are integers
        int xProj = static_cast<int>((point.x + 1.) * width / 2.);
        int yProj = static_cast<int>((point.y + 1.) * height / 2.);
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
//        drawTriangle(p1, p2, p3, image, white);
    }
}


void Model::drawModelWithLight(TGAImage &image,TGAImage &texture, int width, int height, Vector3D lightDirection) {
    projectVerts(width, height);

    for (const auto& face : faces) {
        Point2D p1 = projectedVerts[face.second[0].vertexIndex];
        Point2D p2 = projectedVerts[face.second[1].vertexIndex];
        Point2D p3 = projectedVerts[face.second[2].vertexIndex];
        //Calculate the normal vector of the face
        Point3D v0 = verts[face.second[0].vertexIndex];
        Point3D v1 = verts[face.second[1].vertexIndex];
        Point3D v2 = verts[face.second[2].vertexIndex];

        Vector3D edge1 = Vector3D(v2, v0);
        Vector3D edge2 = Vector3D(v2, v1);
        Vector3D normal = edge2.crossProduct(edge1);
        normal.normalize();
        float intensity = normal.dotProduct(lightDirection);

        if (intensity > 0) {
            //texture points for the face and edited to be within the range of the texture image
            int imgHeight = texture.get_height();
            int imgWidth = texture.get_width();
//            std::cout << imgHeight << " " << imgWidth << std::endl;
            Point2D t1 = projectedVerts[face.second[0].textureIndex];
            Point2D t2 = projectedVerts[face.second[1].textureIndex];
            Point2D t3 = projectedVerts[face.second[2].textureIndex];

            t1.x = t1.x * imgWidth;
            t1.y = t1.y * imgHeight;
            t2.x = t2.x * imgWidth;
            t2.y = t2.y * imgHeight;
            t3.x = t3.x * imgWidth;

            TGAColor colorP1 = texture.get(static_cast<int>(t1.x), static_cast<int>(t1.y));
            TGAColor colorP2 = texture.get(static_cast<int>(t2.x), static_cast<int>(t2.y));
            TGAColor colorP3 = texture.get(static_cast<int>(t3.x), static_cast<int>(t3.y));
            std::vector<TGAColor> colors = {colorP1, colorP2, colorP3};
            drawTriangle(p1, p2, p3, image, colors, intensity);
        }
    }
}