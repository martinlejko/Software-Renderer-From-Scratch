# Software Renderer From Scratch Documentation

## Header File: `graphics.h`

### Overview

The `graphics.h` header file contains fundamental functions to create and render basic geometric shapes within the software renderer.
### Data Structures

#### `struct Point2D`
Represents a 2D point with integer coordinates.

- `int x`: X-coordinate of the point.
- `int y`: Y-coordinate of the point.
### Functions

#### 1. `void drawLine(const Point2D& p1, const Point2D& p2, const TGAColor& color, TGAImage& image)`

- **Description:** Renders a straight line between two given points. The line is drawn using the Bresenham's line drawing algorithm. The algorithm is implemented using integer arithmetic only.
  
  - `p1`: Staring point of the line.
  - `p2`: Ending point of the line.
  - `color`: Color of the line to be drawn.
  - `image`: Image to draw the line on.

#### 2. `void drawTriangle(Point p1, Point p2, Point p3, Color color)`

- **Description:** Renders a filled triangle using three given points.
  
  - `p1`, `p2`, `p3`: Vertices of the triangle.
  - `color`: Color to fill the triangle.

