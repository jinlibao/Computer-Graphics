# Surface of Revolution

## Modifications

Here are three modifications I made:

1. A circle of radius 1/2 centered at (0, 1) revolving around the y-axis (torus)
2. A piecewise function
3. Another piecewise function
4. exp(y / 4)
5. sin(y / 4)
6. cos(y / 4)

## Compiling

The program can be run on either Windows or Mac.

* Windows: you need to uncomment line 7 `#include <windows.h>`, then just build on Visual Studio.
* Mac: run the `make` command in the console would invoke `clang` to compile the program with frameworks `GLUT` and `OpenGL`.

## Generating the .obj file

Function `output` was written to export the mesh to .obj file. The exported .obj files are under the "obj" folder.
