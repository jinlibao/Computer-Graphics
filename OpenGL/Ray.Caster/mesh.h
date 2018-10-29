#ifndef MESH_H
#define MESH_H

#include "matrix.h"
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <istream>
#include <sstream>
#include <string>
#include <vector>

//################# VertexID ###################
class VertexID {
public:
    int vertIndex; // index of this vert in the vertex list
    int textIndex; // index of the texture
    int normIndex; // index of this vertex's normal
};
//#################### Face ##################
class Face {
public:
    int nVerts;     // number of vertices in this face
    VertexID *vert; // the list of vertex and normal indices
    Face()
    {
        nVerts = 0;
        vert = NULL;
    } // constructor
    ~Face()
    {
        delete[] vert;
        nVerts = 0;
    } // destructor
};
//###################### Mesh #######################
class Mesh {
private:
    Point *pt;       // array of 3D vertices
    Vector *texture; // array of textures
    Vector *normal;  // array of normals
    Face *face;      // array of face data
    int numVerts;    // number of vertices in the mesh
    int numTexts;    // number of vertices in the mesh
    int numNorms;    // number of normal vectors for the mesh
    int numFaces;    // number of faces in the mesh
                     // ... others to be added later
public:
    Mesh() { numVerts = numTexts = numNorms = numFaces = 0; } // constructor
    ~Mesh()
    {
        if (numVerts > 0) delete[] pt;
        if (numNorms > 0) delete[] normal;
        if (numTexts > 0) delete[] texture;
        if (numFaces > 0) delete[] face;
        numVerts = numTexts = numNorms = numFaces = 0;
    }                     // destructor
    int readFile(char *); // to read in a filed mesh
    int readmesh(char *);
    int readObj(const char *, const int);
    double X(double, double);
    double Y(double, double);
    double Z(double, double);
    double nx(double, double);
    double ny(double, double);
    double nz(double, double);
    void makeSurfaceMesh();
    void output();
    void draw(int);
};
#endif
