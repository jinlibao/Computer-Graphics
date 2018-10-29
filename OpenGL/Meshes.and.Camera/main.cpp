// main.cpp
// Libao Jin
// ljin1@uwyo.edu
// COSC 5450 Project 2: Meshes and Camera
// Fly throught the wirefram/solid objects with camera.
// Need camera.cpp, camera.h, mesh.cpp, mesh.h, matrix.cpp, matrix.h,
// light.h, material.h

#include "camera.h"
#include "light.h"
#include "material.h"
#include "matrix.h"
#include "mesh.h"
#include <cmath>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>

#if defined __APPLE__ && !defined X11
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

using namespace std;

GLint const WIDTH = 640, HEIGHT = 480;
GLint BitsPerPixel = 32;
int frameNumber = 1;

#ifdef USEFREEIMAGE
#undef USEFREEIMAGE
#define USEFREEIMAGE 1

#include <FreeImage.h>

void saveImage()
{
    BitsPerPixel = 24;
    FreeImage_Initialise();
    // cout << "FreeImage " << FreeImage_GetVersion() << endl;
    // cout << FreeImage_GetCopyrightMessage() << endl;
    FIBITMAP *bitmap = FreeImage_Allocate(WIDTH, HEIGHT, BitsPerPixel);
    GLfloat pixels[3 * WIDTH * HEIGHT];
    glReadPixels(0, 0, WIDTH, HEIGHT, GL_RGB, GL_FLOAT, pixels);
    RGBQUAD color;
    if (!bitmap) exit(1);
    for (int i = 0; i < WIDTH; ++i) {
        for (int j = 0; j < HEIGHT; ++j) {
            color.rgbRed = pixels[3 * (j * WIDTH + i)] * 255;
            color.rgbGreen = pixels[3 * (j * WIDTH + i) + 1] * 255;
            color.rgbBlue = pixels[3 * (j * WIDTH + i) + 2] * 255;
            FreeImage_SetPixelColor(bitmap, i, j, &color);
        }
    }
    char filename[100] = "";
    sprintf(filename, "output/meshes_%03d.png", frameNumber++);
    if (FreeImage_Save(FIF_PNG, bitmap, filename, 0))
        cout << "Image successfully saved: " << filename << endl;
    FreeImage_DeInitialise();
}

#else
#define USEFREEIMAGE 0
void saveImage(){};
#endif

// creating multiple Material objects for later rendering
Material emerald(0.0215, 0.1745, 0.0215, 1.0, 0.07568, 0.61424, 0.07568, 1.0, 0.633, 0.727811, 0.633, 1.0, 0.0, 0.0, 0.0, 1.0, 10.0);
Material silver(0.19225, 0.19225, 0.19225, 1.0, 0.50754, 0.50754, 0.50754, 1.0, 0.508273, 0.508273, 0.508273, 1.0, 0.2, 0.2, 0.2, 1.0, 50.0);
Material libertyMaterial(0.0, 0.0, 0.1, 1.0, 0.195441, 0.263741, 0.2537, 1.0, 0.0237312, 0.0522111, 0.0793909, 1.0, 0.2, 0.7, 0.8, 1.0, 50.0);
Material surfaceMaterial(0.0, 0.5, 0.0, 1.0, 0.0, 0.8, 0.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.2, 0.2, 0.2, 1.0, 60.0);
Material glutWireOjectMaterial(0.0, 0.0, 0.0, 1.0, 0.8, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.2, 0.2, 0.2, 1.0, 80.0);
Material mugMaterial(0.0, 0.0, 0.0, 1.0, 0.4, 0.5, 0.8, 1.0, 1.0, 1.0, 1.0, 1.0, 0.8, 0.4, 0.7, 1.0, 200.0);
Material blueMaterial(0.0, 0.0, 0.8, 1.0, 0.0, 0.0, 0.8, 1.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.8, 1.0, 300.0);
Material greenMaterial(0.2, 0.2, 0.2, 1.0, 0.0, 1.0, 0.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.5, 1.0, 80.0);

// creating multiple Light objects for later rendering
Light light01(0.2, 0.2, 0.2, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.0, GL_LIGHT0);
Light light02(0.2, 0.2, 0.2, 1.0, 0.0, 1.0, 0.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.0, GL_LIGHT0);
Light light03(0.2, 0.2, 0.2, 1.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.0, GL_LIGHT0);
Light light11(0.2, 0.2, 0.2, 1.0, 0.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0, GL_LIGHT1);
Light light12(0.2, 0.2, 0.2, 1.0, 1.0, 0.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0, GL_LIGHT1);
Light light13(0.2, 0.2, 0.2, 1.0, 1.0, 1.0, 0.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0, GL_LIGHT1);
Light light21(0.2, 0.2, 0.4, 1.0, 0.0, 0.0, 0.5, 1.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, GL_LIGHT2);
Light light22(0.2, 0.2, 0.4, 1.0, 0.0, 1.0, 0.5, 0.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, GL_LIGHT2);
Light light23(0.2, 0.2, 0.4, 1.0, 0.0, 1.0, 0.5, 1.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, GL_LIGHT2);
Light light31(0.0, 0.3, 0.0, 1.0, 0.5, 0.5, 0.8, 1.0, 1.0, 1.0, 1.0, 1.0, 0.0, 1.0, 0.0, 0.0, GL_LIGHT3);
Light light32(0.0, 0.3, 0.0, 1.0, 0.5, 0.8, 0.5, 1.0, 1.0, 1.0, 1.0, 1.0, 0.0, 1.0, 0.0, 0.0, GL_LIGHT3);
Light light33(0.0, 0.3, 0.0, 1.0, 0.8, 0.5, 0.5, 1.0, 1.0, 1.0, 1.0, 1.0, 0.0, 1.0, 0.0, 0.0, GL_LIGHT3);

char libertyObjFile[] = "./obj/liberty.statue.simplified.obj";
char mugObjFile[] = "./obj/Mug.obj";
int row = 3, col = 3, layers = 3; // for populating liberty and mug
float theta = 10.0;               // for roll, yaw, pitch
float dist = 5.0;                 // for sliding/moving along u, v, n
GLint modeSwitch = 0;             // 0: Camera Class mode, 1: OpenGL mode
GLfloat bg_r = 1.0;               // background color red
GLfloat bg_g = 1.0;               // background color green
GLfloat bg_b = 1.0;               // background color blue
GLfloat bg_a = 1.0;               // background color alpha
GLfloat ex = 100.0;               // eye position x
GLfloat ey = 100.0;               // eye position y
GLfloat ez = 100.0;               // eye position z
GLfloat lx = 0.0;                 // look point x
GLfloat ly = 0.0;                 // look point y
GLfloat lz = 0.0;                 // look point z
GLfloat ux = 0.0;                 // up vector x
GLfloat uy = 1.0;                 // up vector y
GLfloat uz = 0.0;                 // up vector z
Point eye(ex, ey, ez);
Point look(lx, ly, lz);
Vector up(ux, uy, uz);
Vector u, v, n;
Camera camera;
Mesh mug, liberty, surfaceOfRevolution;

void drawBox()
{
    GLfloat sideLength = 10.0;
    // Normals for the 6 faces of a cube.
    GLfloat n[6][3] = {{-1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {1.0, 0.0, 0.0},
                       {0.0, -1.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, -1.0}};
    // Vertex indices for the 6 faces of a cube.
    GLint faces[6][4] = {{0, 1, 2, 3}, {3, 2, 6, 7}, {7, 6, 5, 4},
                         {4, 5, 1, 0}, {5, 6, 2, 1}, {7, 4, 0, 3}};
    // Setup cube vertex data.
    GLfloat v[8][3];
    v[0][0] = v[1][0] = v[2][0] = v[3][0] = -sideLength;
    v[4][0] = v[5][0] = v[6][0] = v[7][0] = sideLength;
    v[0][1] = v[1][1] = v[4][1] = v[5][1] = -sideLength;
    v[2][1] = v[3][1] = v[6][1] = v[7][1] = sideLength;
    v[0][2] = v[3][2] = v[4][2] = v[7][2] = sideLength;
    v[1][2] = v[2][2] = v[5][2] = v[6][2] = -sideLength;

    for (int i = 0; i < 6; i++) {
        glBegin(GL_QUADS);
        glNormal3fv(&n[i][0]);
        glVertex3fv(&v[faces[i][0]][0]);
        glVertex3fv(&v[faces[i][1]][0]);
        glVertex3fv(&v[faces[i][2]][0]);
        glVertex3fv(&v[faces[i][3]][0]);
        glEnd();
    }
}

void drawGlutObjects()
{
    glutWireOjectMaterial.active();
    glPushMatrix();
    glTranslated(20.0, 0.0, 0.0);
    glutWireSphere(10.0, 20, 20);
    glPopMatrix();

    glPushMatrix();
    glTranslated(20.0, 20.0, 0.0);
    glScaled(10.0, 10.0, 10.0);
    glutWireIcosahedron();
    glPopMatrix();

    glPushMatrix();
    glTranslated(20.0, 40.0, 0.0);
    glScaled(10.0, 10.0, 10.0);
    glutWireTetrahedron();
    glPopMatrix();

    glPushMatrix();
    glTranslated(40.0, 0.0, 0.0);
    glScaled(10.0, 10.0, 10.0);
    glutWireOctahedron();
    glPopMatrix();

    glShadeModel(GL_SMOOTH);
    glPushMatrix();
    glTranslated(40.0, 20.0, 0.0);
    glutSolidTorus(2.0, 5.0, 20, 20);
    glPopMatrix();

    glPushMatrix();
    glTranslated(40.0, 40.0, 0.0);
    glScaled(10.0, 10.0, 10.0);
    glutWireDodecahedron();
    glPopMatrix();

    glPushMatrix();
    glTranslated(0.0, 0.0, 20.0);
    glutWireCube(10.0);
    glPopMatrix();

    glShadeModel(GL_FLAT);
    glPushMatrix();
    glTranslated(0.0, 20.0, 20.0);
    glutSolidCone(5.0, 10.0, 20, 20);
    glPopMatrix();

    glPushMatrix();
    glTranslated(0.0, 40.0, 20.0);
    glutWireTeapot(10.0);
    glPopMatrix();
}

void drawWireframeObjects()
{
    light01.on();
    light11.on();
    light21.on();
    light31.on();

    libertyMaterial.active();
    glShadeModel(GL_SMOOTH);
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            for (int k = 0; k < layers; ++k) {
                glPushMatrix();
                glTranslated(i * 90.0 - 50.0, j * 90.0 - 50., k * 90.0 - 50.);
                glScaled(50.0, 50.0, 50.0);
                glRotated(10 * (i + j + k), i % 3 == 0, j % 3 == 0, k % 3 == 0);
                liberty.draw(0);
                glPopMatrix();
            }
        }
    }

    mugMaterial.active();
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            for (int k = 0; k < layers; ++k) {
                glPushMatrix();
                glTranslated(i * -300.0, j * -300.0, k * -300.0);
                glScaled(30.0, 30.0, 30.0);
                glRotated(10 * (i + j + k), i % 3 == 0, j % 3 == 0, k % 3 == 0);
                mug.draw(1);
                glPopMatrix();
            }
        }
    }

    surfaceMaterial.active();
    glShadeModel(GL_FLAT);
    glPushMatrix();
    glTranslated(0.0, 20.0, 40.0);
    glScaled(5.0, 5.0, 5.0);
    surfaceOfRevolution.draw(0);
    glPopMatrix();

    light03.on();
    light13.on();
    light23.on();
    light33.on();
}

void initCamera()
{
    // Setup the view of the cube.
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.0, (GLfloat)WIDTH / HEIGHT, 1.0, 1000.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(ex, ey, ez, lx, ly, lz, ux, uy, uz);
}

void init()
{
    // Port in meshes from mug.obj and liberty.statue.simpliefied.obj
    mug.readObj(mugObjFile, 3);
    liberty.readObj(libertyObjFile, 4);
    surfaceOfRevolution.makeSurfaceMesh();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(bg_r, bg_g, bg_b, bg_a);

    // Set up camera using Camera class
    glViewport(0, 0, WIDTH, HEIGHT);
    camera.setShape(90.0, (GLfloat)WIDTH / HEIGHT, 1.0, 1000.0);
    camera.set(eye, look, up);

    glEnable(GL_DEPTH_TEST);
    // Set up lights
    glEnable(GL_LIGHTING);
    // Enable a single OpenGL light.
    light01.on();
}

void display()
{
    // camera class mode
    if (modeSwitch == 0) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(bg_r, bg_g, bg_b, bg_a);
        glColor4f(1.0, 0.0, 1.0, 1.0);
        drawWireframeObjects();
        drawGlutObjects();
        drawBox();
    }

    if (USEFREEIMAGE) saveImage();
    glutSwapBuffers();
}

void moveAlongU(float dist) {
    look.set(camera.GetLook());
    eye.set(camera.GetEye());
    Vector u(camera.GetU());
    look.set(look + u * dist);
    eye.set(eye + u * dist);
    camera.set(eye, look, up);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eye.x, eye.y, eye.z, look.x, look.y, look.z, up.x, up.y, up.z);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(bg_r, bg_g, bg_b, bg_a);
    glColor4f(1.0, 0.0, 1.0, 1.0);
    drawWireframeObjects();
    drawGlutObjects();
    drawBox();
}

void moveAlongV(float dist) {
    look.set(camera.GetLook());
    eye.set(camera.GetEye());
    Vector v(camera.GetV());
    look.set(look + v * dist);
    eye.set(eye + v * dist);
    camera.set(eye, look, up);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eye.x, eye.y, eye.z, look.x, look.y, look.z, up.x, up.y, up.z);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(bg_r, bg_g, bg_b, bg_a);
    glColor4f(1.0, 0.0, 1.0, 1.0);
    drawWireframeObjects();
    drawGlutObjects();
    drawBox();
}

void moveAlongN(float dist) {
    look.set(camera.GetLook());
    eye.set(camera.GetEye());
    Vector n(camera.GetN());
    look.set(look + n * dist);
    eye.set(eye + n * dist);
    camera.set(eye, look, up);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eye.x, eye.y, eye.z, look.x, look.y, look.z, up.x, up.y, up.z);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(bg_r, bg_g, bg_b, bg_a);
    glColor4f(1.0, 0.0, 1.0, 1.0);
    drawWireframeObjects();
    drawGlutObjects();
    drawBox();
}

void yaw(float theta)
{
    eye = camera.GetEye();
    ex = eye.x;
    ey = eye.y;
    ez = eye.z;
    v = camera.GetV();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(bg_r, bg_g, bg_b, bg_a);
    glColor4f(1.0, 0.0, 1.0, 1.0);
    glTranslatef(-ex, -ey, -ez);
    glPushMatrix();
    glRotatef(theta, v.x, v.y, v.z);
    drawWireframeObjects();
    drawGlutObjects();
    drawBox();
    glPopMatrix();
    glTranslatef(ex, ey, ez);
}

void roll(float theta) {
    eye = camera.GetEye();
    ex = eye.x;
    ey = eye.y;
    ez = eye.z;
    v = camera.GetN();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(bg_r, bg_g, bg_b, bg_a);
    glColor4f(1.0, 0.0, 1.0, 1.0);
    glTranslatef(-ex, -ey, -ez);
    glPushMatrix();
    glRotatef(theta, v.x, v.y, v.z);
    drawWireframeObjects();
    drawGlutObjects();
    drawBox();
    glPopMatrix();
    glTranslatef(ex, ey, ez);
}

void pitch(float theta) {
    eye = camera.GetEye();
    ex = eye.x;
    ey = eye.y;
    ez = eye.z;
    v = camera.GetU();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(bg_r, bg_g, bg_b, bg_a);
    glColor4f(1.0, 0.0, 1.0, 1.0);
    glTranslatef(-ex, -ey, -ez);
    glPushMatrix();
    glRotatef(theta, v.x, v.y, v.z);
    drawWireframeObjects();
    drawGlutObjects();
    drawBox();
    glPopMatrix();
    glTranslatef(ex, ey, ez);
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case '1':
        modeSwitch == 0 ? camera.slide(0.0, 0.0, dist) : moveAlongN(dist);
        break;
    case '5':
        modeSwitch == 0 ? camera.slide(0.0, 0.0, -dist) : moveAlongN(-dist);
        break;
    case '4':
        modeSwitch == 0 ? camera.slide(dist, 0.0, 0.0) : moveAlongU(dist);
        break;
    case '6':
        modeSwitch == 0 ? camera.slide(-dist, 0.0, 0.0) : moveAlongU(-dist);
        break;
    case '8':
        modeSwitch == 0 ? camera.slide(0.0, dist, 0.0) : moveAlongV(dist);
        break;
    case '2':
        modeSwitch == 0 ? camera.slide(0.0, -dist, 0.0) : moveAlongV(-dist);
        break;
    case 'A':
    case 'a':
        modeSwitch == 0 ? camera.yaw(-theta) : yaw(-theta);
        break;
    case 'D':
    case 'd':
        modeSwitch == 0 ? camera.yaw(theta) : yaw(theta);
        break;
    case 'W':
    case 'w':
        modeSwitch == 0 ? camera.pitch(-theta) : pitch(-theta);
        break;
    case 'S':
    case 's':
        modeSwitch == 0 ? camera.pitch(theta) : pitch(theta);
        break;
    case 'Q':
    case 'q':
        modeSwitch == 0 ? camera.roll(-theta) : roll(-theta);
        break;
    case 'E':
    case 'e':
        modeSwitch == 0 ? camera.roll(theta) : roll(theta);
        break;
    case 'C':
    case 'c':
        ++modeSwitch %= 2;
        if (modeSwitch) {
            bg_r = 0.7;
            bg_g = 0.7;
            bg_b = 0.7;
            printf("mode: OpenGL\n");
        }
        else {
            bg_r = 1.0;
            bg_g = 1.0;
            bg_b = 1.0;
            printf("mode: Camera class\n");
        }
        break;
    case 27:
        exit(0);
        break;
    default:
        break;
    }
    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("COSC 5450 Project 2: Meshes and Camera by Libao Jin");
    init();
    glutKeyboardFunc(keyboard);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
