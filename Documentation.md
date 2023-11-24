# Software Renderer From Scratch Documentation

## Files: `graphics.h & graphics.cpp`

### Overview

The `graphics.h & graphics.cpp` contains fundamental functions to create and render basic geometric shapes within the software renderer.

### Functions

#### `void drawLine(const Point2D& p1, const Point2D& p2, const TGAColor& color, TGAImage& image)`

- **Description:** Renders a straight line between two given points. The line is drawn using the Bresenham's line drawing algorithm. The algorithm is implemented using integer arithmetic only.
  
  - `p1`: Staring point of the line.
  - `p2`: Ending point of the line.
  - `color`: Color of the line to be drawn.
  - `image`: Image to draw the line on.

####`void drawTriangle(const Point2D& p1, const Point2D& p2, const Point2D& p3, const TGAColor& color, TGAImage& image)`

- **Description:** Renders a filled triangle using three given points.
  
  - `p1`, `p2`, `p3`: Vertices of the triangle.
  - `color`: Color to fill the triangle.
  - `image`: Image to draw the triangle on.

## Files: `datatypes.h`

### Overview

The `datatypes.h` contains the definition of custom data types used in the software renderer. Some also have mathematical operations defined on them.

#### `struct Point2D`
Represents a 2D point with integer coordinates.

- `int x`: X-coordinate of the point.
- `int y`: Y-coordinate of the point.

#### `struct Point3D`
Represents a 3D point with integer coordinates.

- `int x`: X-coordinate of the point.
- `int y`: Y-coordinate of the point.
- `int z`: Z-coordinate of the point.

#### `struct FaceElement`
Faces are defined using lists of vertex, texture and normal indices in the format vertex index/texture index/normal index. We start indexing from 1.

- `int textureIndex`
- `int vertexIndex`
- `int normalIndex`


## Files: `model.h & model.cpp`

### Overview

The `model.h & model.cpp` contains the definition of the `Model` class. The class is used to load and render 3D models in the software renderer. The models are loaded from `.obj` files. The class also contains parsing functions to parse the `.obj` files. 

### Variables
- `unordered_map<int, Point3D> verts`: Stores the vertices of the model with the index of the vertex.
- `unordered_map<int, vector<FaceElement> faces`: Stores faces of the model with the index into a custom strcutre `FaceElement`.
- `unordered_map<int, Point2D> projectedVerts`: Stores orthographically projected vertices of the model with the index of the vertex. The vertices are projected onto the XY plane.

### Functions
- `Model(const char *filename)`: Default constructor that utilizes parseModelFile function.
- `ParseModelFile()`: Parses the `.obj` file and stores the vertices and faces in the `verts` and `faces` variables. For more information check the [Wavefront .obj file format](https://en.wikipedia.org/wiki/Wavefront_.obj_file).
- `int nverts() const`: Returns the number of vertices in the model.
- `int nfaces() const`: Returns the number of faces in the model.
- `printVerticesAndFaces() const`: Prints the vertices and faces of the model. For debugging purposes.
- `void projectVerts()`: Orthographically projects the vertices of the model onto the XY plane. From 3D to 2D.
- `void drawModel(TGAImage& image)`: Renders the model onto the given image.
