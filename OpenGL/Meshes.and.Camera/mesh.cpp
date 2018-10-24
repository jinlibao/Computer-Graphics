// #define X11 X11
#include "mesh.h"

#if defined __APPLE__ && !defined X11
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

#include <cassert>
#include <iostream>
#include <math.h>
#include <sstream>
#include <string>

using namespace std;

int Mesh::readmesh(char *fileName)
{
    fstream infile;
    infile.open(fileName, ios::in);
    if (infile.fail()) return -1; // error - can't open file
    if (infile.eof()) return -1;  // error - empty file
    infile >> numVerts >> numNorms >> numFaces;
    pt = new Point[numVerts];
    normal = new Vector[numNorms];
    face = new Face[numFaces];
    // check that enough memory was found:
    if (!pt || !normal || !face) return -1; // out of memory
    for (int p = 0; p < numVerts; p++)      // read the vertices
        infile >> pt[p].x >> pt[p].y >> pt[p].z;
    for (int n = 0; n < numNorms; n++) // read the normals
        infile >> normal[n].x >> normal[n].y >> normal[n].z;
    for (int f = 0; f < numFaces; f++) // read the faces
    {
        infile >> face[f].nVerts;
        face[f].vert = new VertexID[face[f].nVerts];
        for (int i = 0; i < face[f].nVerts; i++)
            infile >> face[f].vert[i].vertIndex >> face[f].vert[i].normIndex;
    }
    return 0; // success
}

int Mesh::readObj(const char *fileName, const int nVerts = 3)
{
    numVerts = 0;
    numTexts = 0;
    numNorms = 0;
    numFaces = 0;
    fstream infile;
    infile.open(fileName, ios::in);
    if (infile.fail() || infile.eof()) return -1;
    vector<string> vlines;
    vector<string> vtlines;
    vector<string> vnlines;
    vector<string> flines;
    string line;

    while (getline(infile, line)) {
        if (line.size() < 3) continue;
        string type(line.substr(0, 2));
        string v(line.substr(2));
        if (type == "v ") {
            vlines.push_back(v);
            ++numVerts;
        }
        else if (type == "vt") {
            vtlines.push_back(v);
            ++numTexts;
        }
        else if (type == "vn") {
            vnlines.push_back(v);
            ++numNorms;
        }
        else if (type == "f ") {
            flines.push_back(v);
            ++numFaces;
        }
    }

    cout << numVerts << ' ' << numNorms << ' ' << numTexts << ' ' << numFaces
         << endl;

    if (numVerts > 0) {
        pt = new Point[numVerts];
        for (int p = 0; p < numVerts; ++p) {
            istringstream s(vlines[p]);
            s >> pt[p].x >> pt[p].y >> pt[p].z;
        }
    }
    if (numTexts > 0) {
        texture = new Vector[numTexts];
        for (int t = 0; t < numTexts; ++t) {
            istringstream s(vtlines[t]);
            s >> texture[t].x >> texture[t].y >> texture[t].z;
        }
    }
    if (numNorms > 0) {
        normal = new Vector[numNorms];
        for (int n = 0; n < numNorms; ++n) {
            istringstream s(vnlines[n]);
            s >> normal[n].x >> normal[n].y >> normal[n].z;
        }
    }
    if (numFaces > 0) {
        face = new Face[numFaces];
        for (int i = 0; i < numFaces; ++i) {
            face[i].nVerts = nVerts;
            face[i].vert = new VertexID[face[i].nVerts];
            int *index = new int[face[i].nVerts * 2];
            if (face[i].nVerts == 4)
                sscanf(flines[i].c_str(), "%d//%d %d//%d %d//%d %d//%d", index,
                       index + 1, index + 2, index + 3, index + 4, index + 5,
                       index + 6, index + 7);
            if (face[i].nVerts == 3)
                sscanf(flines[i].c_str(), "%d//%d %d//%d %d//%d", index,
                       index + 1, index + 2, index + 3, index + 4, index + 5);
            for (int j = 0; j < face[i].nVerts; ++j) {
                face[i].vert[j].vertIndex = --index[2 * j];
                face[i].vert[j].normIndex = --index[2 * j + 1];
            }
            // for (int i = 0; i < face[f].nVerts; ++i) {
            // istringstream s(flines[f]);
            // s >> face[f].vert[i].vertIndex >> face[f].vert[i].normIndex;
            // face[f].vert[i].vertIndex--;
            // face[f].vert[i].normIndex--;
            // }
            delete[] index;
        }
    }
    return 0;
}

// double Mesh::X(double u, double v) { return u * sin(v); }
//
// double Mesh::Y(double u, double v)
// {
//     double pi = 4 * atan(1);
//     if (u < -pi / 4)
//         return (u + pi / 2);
//     else if (u < 0)
//         return -u;
//     else if (u < pi / 4)
//         return u;
//     else
//         return (-u + pi / 2);
// }
//
// double Mesh::Z(double u, double v) { return u * cos(v); }

double Mesh::X(double u, double v) { return cos(2 * u) * cos(v); }
double Mesh::Y(double u, double v) { return u; }
double Mesh::Z(double u, double v) { return cos(2 * u) * sin(v); }
double Mesh::nx(double u, double v) { return ((-1 * cos(u)) * X(u, v)); }
double Mesh::ny(double u, double v) { return ((-1 * cos(u)) * Y(u, v)); }
double Mesh::nz(double u, double v) { return ((-1 * cos(u)) * Z(u, v)); }

void Mesh::makeSurfaceMesh()
{
    int i, j, numValsU = 100, numValsV = 100; // set these
    double u, v, uMin = -3.14 / 2, vMin = 0, uMax = 3.14 / 2, vMax = 2 * 3.14;
    double delU = (uMax - uMin) / (numValsU - 1);
    double delV = (vMax - vMin) / (numValsV - 1);
    numVerts = numValsU * numValsV + 1;         // total # of vertices
    numFaces = (numValsU - 1) * (numValsV - 1); // # of faces
    numNorms = numVerts; // for smooth shading - one normal per vertex
    pt = new Point[numVerts];
    assert(pt != NULL); // make space
    face = new Face[numFaces];
    assert(face != NULL);
    normal = new Vector[numNorms];
    assert(normal != NULL);
    for (i = 0, u = uMin; i < numValsU; i++, u += delU)
        for (j = 0, v = vMin; j < numValsV; j++, v += delV) {
            int whichVert =
                i * numValsV + j; // index of the vertex and normal
                                  // set this vertex: use functions X, Y, and Z
            pt[whichVert].set(X(u, v), Y(u, v), Z(u, v));
            // set the normal at this vertex: use functions nx, ny, nz
            normal[whichVert].set(nx(u, v), ny(u, v), nz(u, v));
            normal[whichVert].normalize();
            // make quadrilateral
            if (i > 0 && j > 0) // when to compute next face
            {
                int whichFace = (i - 1) * (numValsV - 1) + (j - 1);
                face[whichFace].vert = new VertexID[4];
                assert(face[whichFace].vert != NULL);
                face[whichFace].nVerts = 4;
                face[whichFace].vert[0].vertIndex = // same as norm index
                    face[whichFace].vert[0].normIndex = whichVert;
                face[whichFace].vert[1].vertIndex =
                    face[whichFace].vert[1].normIndex = whichVert - 1;
                face[whichFace].vert[2].vertIndex =
                    face[whichFace].vert[2].normIndex =
                        whichVert - numValsV - 1;
                face[whichFace].vert[3].vertIndex =
                    face[whichFace].vert[3].normIndex = whichVert - numValsV;
            }
        }
}

void Mesh::output()
{
    for (int i = 0; i < numVerts; ++i) {
        printf("v ");
        printf("%f %f %f\n", pt[i].x, pt[i].y, pt[i].z);
    }
    for (int i = 0; i < numNorms; ++i) {
        printf("vn ");
        printf("%f %f %f\n", normal[i].x, normal[i].y, normal[i].z);
    }
    for (int f = 0; f < numFaces; f++) {
        printf("f");
        for (int v = 0; v < face[f].nVerts; v++) {
            int in = face[f].vert[v].normIndex;
            int iv = face[f].vert[v].vertIndex;
            printf(" %d//%d", in + 1, iv + 1);
        }
        printf("\n");
    }
}

// use OpenGL to draw this mesh
void Mesh::draw(int option = 0)
{
    for (int f = 0; f < numFaces; f++) { // draw each face
        if (option == 0)
            glBegin(GL_QUADS);
        else
            glBegin(GL_LINES);
        // int in = face[f].vert[0].normIndex; // index of this normal
        // glNormal3f(normal[in].x, normal[in].y, normal[in].z);
        for (int v = 0; v < face[f].nVerts; v++) { // for each one..
            int in = face[f].vert[v].normIndex;    // index of this normal
            int iv = face[f].vert[v].vertIndex; // index of this vertex
            glNormal3f(normal[in].x, normal[in].y, normal[in].z);
            glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
        }
        glEnd();
    }
}
