// Libao Jin
// ljin1@uwyo.edu
// #define X11 X11
#if defined __APPLE__ && !defined X11
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif
#include <cstring>
#include <cstdio>
#include <cmath>
#include <FreeImage.h>
#include <iostream>
#include <fstream>

#define WIDTH 640
#define HEIGHT 480
#define BitsPerPixel 24

using namespace std;

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


void saveImage() {
    FreeImage_Initialise();
    cout << "FreeImage " << FreeImage_GetVersion() << endl;
    cout << FreeImage_GetCopyrightMessage() << endl;
    FIBITMAP *bitmap = FreeImage_Allocate(WIDTH, HEIGHT, BitsPerPixel);
    GLfloat pixels[3 * WIDTH * HEIGHT];
    glReadPixels(0, 0, WIDTH, HEIGHT, GL_RGB, GL_FLOAT, pixels);
    RGBQUAD color;
    if (!bitmap)
        exit(1);
    for (int i = 0; i < WIDTH; ++i) {
        for (int j = 0; j < HEIGHT; ++j) {
            color.rgbRed = pixels[3 * (j * WIDTH + i)] * 255;
            color.rgbGreen = pixels[3 * (j * WIDTH + i) + 1] * 255;
            color.rgbBlue = pixels[3 * (j * WIDTH + i) + 2] * 255;
            FreeImage_SetPixelColor(bitmap, i, j, &color);
        }
    }
    char filename[100] = "";
    sprintf(filename, "output.png");
    printf("%s\n", filename);
    if (FreeImage_Save(FIF_PNG, bitmap, filename, 0))
        cout << "Image succesfully saved!\n";
    FreeImage_DeInitialise();
}

void draw(GLfloat *amb1, GLfloat *amb2, GLfloat *amb3, GLfloat *amb4, GLfloat *amb5,
        GLfloat *dif1, GLfloat *dif2, GLfloat *dif3, GLfloat *dif4, GLfloat *dif5,
        GLfloat *spe1, GLfloat *spe2, GLfloat *spe3, GLfloat *spe4, GLfloat *spe5,
        GLfloat shini1, GLfloat shini2, GLfloat shini3, GLfloat shini4, GLfloat shini5) {

    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT, amb1);
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE, dif1);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spe1);
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS, shini1);

    glPushMatrix();
    glTranslated(0, 1, 0);
    glutSolidSphere(0.25, 10, 8);
    glPopMatrix();

    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT, amb2);
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE, dif2);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spe2);
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS, shini2);

    glPushMatrix();
    glTranslated(-0.5, -0.2, 0.2);
    glutSolidCone(0.2, 0.5, 10, 8);
    glPopMatrix();

    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT, amb3);
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE, dif3);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spe3);
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS, shini3);

    glPushMatrix();
    glTranslated(-2, 1, 1);
    glutSolidTeapot(0.2);
    glPopMatrix();

    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT, amb4);
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE, dif4);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spe4);
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS, shini4);

    glPushMatrix();
    glTranslated(1, 1, 1);
    glRotated(90.0, 1, 0, 0);
    glutSolidTorus(0.1, 0.3, 10, 10);
    glPopMatrix();

    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT, amb5);
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE, dif5);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spe5);
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS, shini5);

    glPushMatrix();
    glTranslated(1, 1.5, 1);
    glTranslated(1.0, 0 , 0); // dodecahedron at (1,0,0)
    glScaled(0.15, 0.15, 0.15);
    glutSolidDodecahedron();
    glPopMatrix();
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<< displayWire >>>>>>>>>>>>>>>>>>>>>>
void displayObjects(void) {
    glMatrixMode(GL_PROJECTION); // set the view volume shape
    glLoadIdentity();
    glOrtho(-2.0*64/48.0, 2.0*64/48.0, -2.0, 2.0, 0.1, 100);
    Camera camera;
    Point3 eye(100.0f, 100.0f, 100.0f);
    Point3 look(0.0f, 0.0f, 0.0f);
    Vector3 up(0.0f, 1.0f, 0.0f);
    camera.set(eye, look, up);

    glMatrixMode(GL_MODELVIEW); // position and aim the camera
    glLoadIdentity();
    gluLookAt(2.0, 2.0, 2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3d(1, 0, 0); // draw black lines

    glDisable(GL_LIGHT0);

    glPushMatrix();
    glTranslated(0, 1.5, -1); //lightPos
    glutSolidSphere(0.1, 10, 10);
    glPopMatrix();

    glEnable(GL_LIGHT0);

    GLfloat amb1[] = {0.6f, 0.6f, 0.6f, 0.5f};  // ambient
    GLfloat amb2[] = {1.0f, 0.0f, 0.0f, 1.0f};  // ambient
    GLfloat amb3[] = {0.6f, 0.6f, 1.0f, 0.3f};  // ambient
    GLfloat amb4[] = {0.6f, 1.0f, 0.6f, 0.4f};  // ambient
    GLfloat amb5[] = {1.0f, 0.0f, 1.0f, 0.5f};  // ambient
    GLfloat dif1[] = {0.9f, 0.9f, 0.9f, 0.5f};  // diffuse
    GLfloat dif2[] = {1.0f, 0.0f, 0.0f, 1.0f};  // diffuse
    GLfloat dif3[] = {0.9f, 0.9f, 1.0f, 0.3f};  // diffuse
    GLfloat dif4[] = {0.9f, 1.0f, 0.9f, 0.4f};  // diffuse
    GLfloat dif5[] = {1.0f, 0.0f, 1.0f, 0.5f};  // diffuse
    GLfloat spe1[] = {1.0f, 1.0f, 1.0f, 1.0f};  // specular
    GLfloat spe2[] = {1.0f, 1.0f, 1.0f, 1.0f};  // specular
    GLfloat spe3[] = {1.0f, 1.0f, 1.0f, 1.0f};  // specular
    GLfloat spe4[] = {1.0f, 1.0f, 1.0f, 1.0f};  // specular
    GLfloat spe5[] = {1.0f, 1.0f, 1.0f, 1.0f};  // specular
    GLfloat shini1 = 200.0f;                    // shininess sphere
    GLfloat shini2 = 7.0f;                      // shininess cone
    GLfloat shini3 = 7.0f;                      // shininess teapot
    GLfloat shini4 = 7.0f;                      // shininess torus
    GLfloat shini5 = 7.0f;                      // shininess dodecahedron
    draw(amb1, amb2, amb3, amb4, amb5, dif1, dif2, dif3, dif4, dif5, spe1,
         spe2, spe3, spe4, spe5, shini1, shini2, shini3, shini4, shini5);

    saveImage();
    glFlush();
    glutSwapBuffers();
}

void initMaterial() {

}

void initLighting() {
    glEnable(GL_LIGHTING);
    GLfloat light1Ka[] = {1.0f, 1.0f, 1.0f, 1.0f};   // ambient light
    GLfloat light1Kd[] = {1.0f, 1.0f, 1.0f, 1.0f};   // diffuse light
    GLfloat light1Ks[] = {1.0f, 1.0f, 1.0f, 1.0f};   // specular light
    glLightfv(GL_LIGHT1, GL_AMBIENT, light1Ka);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1Kd);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light1Ks);
    // position the light
    GLfloat light1Pos[4] = {0.0f, 0.0f, 0.0f, 1};
    glLightfv(GL_LIGHT1, GL_POSITION, light1Pos);
    glEnable(GL_LIGHT1);  // MUST enable each light source after configuration
}

void test() {
    Vector3 v1, v2(4.0f, -2.0f, 1.0f), v3(v2);
    v1.print();
    v2.print();
    v3.print();
    v3.flip();
    v3.print();
    v3.set(v1);
    v3.print();
    v3.set(1.0f, -1.0f, 3.0f);
    v3.print();
    v2.print();
    Vector3 v4(v2.cross(v3));
    v4.print();
    v4.normalize();
    v4.print();
    cout << v2.dot(v3) << endl;
}

//<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(100, 100);
    char title[] = "COSC 5450 Project 2: Meshes and Camera";
    glutCreateWindow(title);
    glutDisplayFunc(displayObjects);
    glEnable(GL_DEPTH_TEST);
    glClearColor(1.0f, 1.0f, 1.0f,0.0f);  // background is white
    //glEnable(GL_FLAT);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_SMOOTH);
    glViewport(0, 0, 640, 480);
    glutMainLoop();
}

