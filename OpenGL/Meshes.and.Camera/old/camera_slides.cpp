class Point3 {
    public:
        float x, y, z;

        // Constructor 1
        Point3 (float x, float y, float z) {
            this->x = x;
            this->y = y;
            this->z = z;
        }
        // Constructor 2
        Point3 () : Point3(0.0f, 0.0f, 0.0f) {}
        // Constructor 3
        Point3 (const Point3& p) : Point3(p.x, p.y, p.z) {}

        void set(float x, float y, float z) {
            this->x = x;
            this->y = y;
            this->z = z;
        }

        void set(Point3& p) {
            set(p.x, p.y, p.z);
        }

        void build4tuple(float v[]) {
            v[0] = x;
            v[1] = y;
            v[2] = z;
            v[3] = 1.0f;
        }

        void print() {
            cout << ' ' << x
                 << ' ' << y
                 << ' ' << z << endl;
        }
};

class Vector3 {
    public:
        float x, y, z;

        // Constructor 1
        Vector3 (float x, float y, float z) {
            this->x = x;
            this->y = y;
            this->z = z;
        }
        // Constructor 2
        Vector3 () : Vector3 (0.0f, 0.0f, 0.0f) {}
        // Constructor 3
        Vector3 (const Vector3& v) : Vector3 (v.x, v.y, v.z) {}

        void set(float x, float y, float z) {
            this->x = x;
            this->y = y;
            this->z = z;
        }

        void set(Vector3 v) {
            set(v.x, v.y, v.z);
        }

        void flip() {
            set(-x, -y, -z);
        }

        void setDiff(Point3& a, Point3& b) {
            set(a.x - b.x, a.y - b.y, a.z - b.z);
        }

        void normalize() {
            float norm = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
            set(x / norm, y / norm, z / norm);
        }

        Vector3 cross(Vector3 b) {
            Vector3 ret(y * b.z - b.y * z, z * b.x - x * b.z, x * b.y - y * b.x);
            return ret;
        }

        float dot(Vector3 b) {
            return x * b.x + y * b.y + z * b.z;
        }

        void print() {
            cout << ' ' << x
                 << ' ' << y
                 << ' ' << z << endl;
        }
};

class Camera {
    private:
        Point3 eye;
        Vector3 u, v, n;
        double viewAngle, aspect, nearDist, farDist;
        // void setModelviewMatrix();

    public:
        Camera();

        void set(Point3 eye, Point3 look, Vector3 up) {
            this->eye.set(eye);
            n.set(eye.x - look.x, eye.y - look.y, eye.z - look.z);
            n.normalize();
            u.set(up.cross(n));
            u.normalize();
            v.set(n.cross(u));
            v.normalize();
            setModelviewMatrix();
        }

        void setModelviewMatrix() {
            float m[16];
            Vector3 eyeVec(eye.x, eye.y, eye.z);
            m[0] = u.x; m[4] = u.y; m[8] = u.z; m[12] = -eyeVec.dot(u);
            m[1] = v.x; m[5] = v.y; m[9] = v.z; m[13] = -eyeVec.dot(v);
            m[2] = n.x; m[6] = n.y; m[10] = n.z; m[14] = -eyeVec.dot(n);
            m[3] = 0.0; m[7] = 0.0; m[11] = 0.0; m[15] = 1.0;
            glMatrixMode(GL_MODELVIEW);
            glLoadMatrixf(m);
        }

        void roll(float angle) {
            double pi = 4 * atan(1);
            float cs = cos(pi / 180 * angle);
            float sn = sin(pi / 180 * angle);

            Vector3 t(u);
            u.set(cs * t.x - sn * v.x, cs * t.y - sn * v.y, cs * t.z - sn * v.z);
            v.set(sn * t.x + cs * v.x, sn * t.y + cs * v.y, sn * t.z + cs * v.z);
            setModelviewMatrix();
        }

        void pitch(float angle);
        void yaw(float angle);
        void slide (float delU, float delV, float delN) {
            eye.x += delU * u.x + delV * v.x + delN * n.x;
            eye.y += delU * u.y + delV * v.y + delN * n.y;
            eye.z += delU * u.z + delV * v.z + delN * n.z;
            setModelviewMatrix();
        }
};

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
};


