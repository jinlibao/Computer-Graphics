#pragma once
//@@@@@@@@@@@@@@@@@@ Point3 class @@@@@@@@@@@@@@@@
class Point3 {
public:
    float x, y, z;
    void set(float dx, float dy, float dz) { x = dx; y = dy; z = dz; }
    void set(Point3& p) { x = p.x; y = p.y; z = p.z; }
    Point3(float xx, float yy, float zz) { x = xx; y = yy; z = zz; }
    Point3() { x = y = z = 0; }
    void build4tuple(float v[])
    {// load 4-tuple with this color: v[3] = 1 for homogeneous
        v[0] = x; v[1] = y; v[2] = z; v[3] = 1.0f;
    }
};
//@@@@@@@@@@@@@@@@@@ Vector3 class @@@@@@@@@@@@@@@@
class Vector3 {
public:
    float x, y, z;
    void set(float dx, float dy, float dz) { x = dx; y = dy; z = dz; }
    void set(Vector3& v) { x = v.x; y = v.y; z = v.z; }
    void flip() { x = -x; y = -y; z = -z; } // reverse this vector
    void setDiff(Point3& a, Point3& b)//set to difference a - b
    {
        x = a.x - b.x; y = a.y - b.y; z = a.z - b.z;
    }
    void normalize()//adjust this vector to unit length
    {
        double sizeSq = x * x + y * y + z * z;
        if (sizeSq < 0.0000001)
        {
            //    cerr << "\nnormalize() sees vector (0,0,0)!";
            return; // does nothing to zero vectors;
        }
        float scaleFactor = 1.0 / (float)sqrt(sizeSq);
        x *= scaleFactor; y *= scaleFactor; z *= scaleFactor;
    }
    Vector3(float xx, float yy, float zz) { x = xx; y = yy; z = zz; }
    Vector3(Vector3& v) { x = v.x; y = v.y; z = v.z; }
    Vector3() { x = y = z = 0; } //default constructor
    Vector3 cross(Vector3 b) //return this cross b
    {
        Vector3 c(y*b.z - z*b.y, z*b.x - x*b.z, x*b.y - y*b.x);
        return c;
    }
    float dot(Vector3 b) // return this dotted with b
    {
        return x * b.x + y * b.y + z * b.z;
    }
};
//################# VertexID ###################
class VertexID {
public:
    int vertIndex; // index of this vert in the vertex list
    int normIndex; // index of this vertex's normal
};
//#################### Face ##################
class Face {
public:
    int nVerts; // number of vertices in this face
    VertexID * vert; // the list of vertex and normal indices
    Face() { nVerts = 0; vert = NULL; } // constructor
    ~Face() { delete[] vert; nVerts = 0; } // destructor
};
//###################### Mesh #######################
class Mesh {
private:
    int numVerts;    // number of vertices in the mesh
    Point3* pt;          // array of 3D vertices
    int numNorms;   // number of normal vectors for the mesh
    Vector3 *norm;    // array of normals
    int numFaces;     // number of faces in the mesh
    Face* face;          // array of face data
                         // ... others to be added later
public:
    Mesh() {}         // constructor
    ~Mesh();          // destructor
    int readFile(char * fileName);  // to read in a filed mesh
                                    //.. others ..

    int readmesh(char * fileName)
    {
        fstream infile;
        infile.open(fileName, ios::in);
        if (infile.fail()) return -1; // error - can't open file
        if (infile.eof())  return -1; // error - empty file
        infile >> numVerts >> numNorms >> numFaces;
        pt = new Point3[numVerts];
        norm = new Vector3[numNorms];
        face = new Face[numFaces];
        //check that enough memory was found:
        if (!pt || !norm || !face)return -1; // out of memory
        for (int p = 0; p < numVerts; p++) // read the vertices
            infile >> pt[p].x >> pt[p].y >> pt[p].z;
        for (int n = 0; n < numNorms; n++) // read the normals
            infile >> norm[n].x >> norm[n].y >> norm[n].z;
        for (int f = 0; f < numFaces; f++)// read the faces
        {
            infile >> face[f].nVerts;
            face[f].vert = new VertexID[face[f].nVerts];
            for (int i = 0; i < face[f].nVerts; i++)
                infile >> face[f].vert[i].vertIndex
                >> face[f].vert[i].normIndex;
        }
        return 0; // success
    }

    // Original Code
    /*
    double X(double u, double v) {
        return (cos(u)*cos(v));
    }
    double Y(double u, double v) {
        return (cos(v)*sin(u));
    }

    double Z(double u, double v) {
        return (sin(v));
    }
    */

    // Modification 1: A circle of radius 1/2 centered at (1, 0) revolving around y (torus)
    /*
    double X(double u, double v) {
        return cos(v) * (1.0 / 2 * cos(2 * u) + 1);
    }

    double Y(double u, double v) {
        return 1.0 / 2 * sin(2 * u);
    }

    double Z(double u, double v) {
        return sin(v) * (1.0 / 2 * cos(2 * u) + 1);
    }
    */

    // Modification 2: Curve is a piecewise function
    double X(double u, double v) {
        return u * sin(v);
    }
    double Y(double u, double v) {
        double pi = 4 * atan(1);
        if (u < -pi / 4)
            return (u + pi / 2);
        else if (u < 0)
            return -u;
        else if (u < pi / 4)
            return u;
        else
            return (-u + pi / 2);
    }
    double Z(double u, double v) {
        return u * cos(v);
    }

    // Modification 3: Curve is another piecewise function
    /*
    double X(double u, double v) {
        double pi = 4 * atan(1);
        double x;
        if (u < -pi / 4)
            x = u + pi / 2;
        else if (u < 0)
            x = -u;
        else if (u < pi / 4)
            x = u;
        else
            x = pi / 2 - u;
        return x * cos(v);
    }
    double Y(double u, double v) {
        return u;
    }
    double Z(double u, double v) {
        double pi = 4 * atan(1);
        double x;
        if (u < -pi / 4)
            x = u + pi / 2;
        else if (u < 0)
            x = -u;
        else if (u < pi / 4)
            x = u;
        else
            x = pi / 2 - u;
        return x * sin(v);
    }
    */

    // Modification 4: Curve is exp(y / 4)
    /*
    double X(double u, double v) {
        return exp(u / 4) * cos(v);
    }
    double Y(double u, double v) {
        return u;
    }
    double Z(double u, double v) {
        return exp(u / 4) * sin(v);
    }
    */

    // M4dification 5: Curve is sin(y / 4)
    /*
    double X(double u, double v) {
        return sin(u / 4) * cos(v);
    }
    double Y(double u, double v) {
        return u;
    }
    double Z(double u, double v) {
        return sin(u / 4) * sin(v);
    }
    */

    // M4dification 6: Curve is cos(y / 4)
    /*
    double X(double u, double v) {
        return cos(u / 4) * cos(v);
    }
    double Y(double u, double v) {
        return u;
    }
    double Z(double u, double v) {
        return cos(u / 4) * sin(v);
    }
    */

    double nx(double u, double v) {
        return((-1 * cos(u))*X(u, v));
    }
    double ny(double u, double v) {
        return((-1 * cos(u))*Y(u, v));
    }
    double nz(double u, double v) {
        return((-1 * cos(u))*Z(u, v));
    }
    void makeSurfaceMesh()
    {
        int i, j, numValsU = 100, numValsV = 100;// set these
        double u, v, uMin = -3.14 / 2, vMin = 0, uMax = 3.14 / 2, vMax = 2 * 3.14;
        double delU = (uMax - uMin) / (numValsU - 1);
        double delV = (vMax - vMin) / (numValsV - 1);
        numVerts = numValsU * numValsV + 1; // total # of vertices
        numFaces = (numValsU - 1) * (numValsV - 1); // # of faces
        numNorms = numVerts; // for smooth shading - one normal per vertex
        pt = new Point3[numVerts];  assert(pt != NULL); // make space
        face = new Face[numFaces];    assert(face != NULL);
        norm = new Vector3[numNorms]; assert(norm != NULL);
        for (i = 0, u = uMin; i < numValsU; i++, u += delU)
            for (j = 0, v = vMin; j < numValsV; j++, v += delV)
            {
                int whichVert = i * numValsV + j; //index of the vertex and normal
                                                  // set this vertex: use functions X, Y, and Z
                pt[whichVert].set(X(u, v), Y(u, v), Z(u, v));
                // set the normal at this vertex: use functions nx, ny, nz
                norm[whichVert].set(nx(u, v), ny(u, v), nz(u, v));
                norm[whichVert].normalize();
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
                        face[whichFace].vert[2].normIndex = whichVert - numValsV - 1;
                    face[whichFace].vert[3].vertIndex =
                        face[whichFace].vert[3].normIndex = whichVert - numValsV;
                }
            }
    }
    void output() {
        for (int i = 0; i < numVerts; ++i) {
            printf("v ");
            printf("%f %f %f\n", pt[i].x, pt[i].y, pt[i].z);
        }
        for (int i = 0; i < numNorms; ++i) {
            printf("vn ");
            printf("%f %f %f\n", norm[i].x, norm[i].y, norm[i].z);
        }
        for (int f = 0; f < numFaces; f++) // draw each face
        {
            printf("f");
            for (int v = 0; v < face[f].nVerts; v++) // for each one..
            {
                int in = face[f].vert[v].normIndex; // index of this normal
                int iv = face[f].vert[v].vertIndex; // index of this vertex
                // glNormal3f(norm[in].x, norm[in].y, norm[in].z);
                // glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
                printf(" %d//%d", in + 1, iv + 1);
            }
            printf("\n");
        }
    }

    void draw() // use OpenGL to draw this mesh
    {
        for (int f = 0; f < numFaces; f++) // draw each face
        {
            // glBegin(GL_POLYGON);
            glBegin(GL_LINES);
            for (int v = 0; v < face[f].nVerts; v++) // for each one..
            {
                int in = face[f].vert[v].normIndex; // index of this normal
                int iv = face[f].vert[v].vertIndex; // index of this vertex
                glNormal3f(norm[in].x, norm[in].y, norm[in].z);
                glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
            }
            glEnd();
        }
    }
};
