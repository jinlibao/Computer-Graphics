// main.cpp
// COSC 5450 Project 3(a): RayCaster
// Libao Jin
// ljin1@uwyo.edu

#include "camera.h"
#include "color.h"
#include "light.h"
#include "matrix.h"
#include "object.h"
#include "ray.h"
#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>

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

GLint const WIDTH = 500, HEIGHT = 400;
GLfloat const ASPECT = (GLfloat)WIDTH / HEIGHT;
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
    sprintf(filename, "output/raycast_%03d.png", frameNumber++);
    if (FreeImage_Save(FIF_PNG, bitmap, filename, 0))
        cout << "Image successfully saved: " << filename << endl;
    FreeImage_DeInitialise();
}

#else
#define USEFREEIMAGE 0
void saveImage(){};
#endif

// set parameters for lights
Light globalAmbient();
globalAmbient.setGlobalAmbient(0.25, 0.05, 0.05, 1);
Light pointLight(0.65, 0.65, 0.65, 1, 0, 0, 0, 1, 0, 0, 0, 1, 200, 100, 50, 1, GL_LIGHT0);
Light spotLight(0, 0, 0, 1, 0, 0, 0, 1, 0.4, 0.4, 0.7, 1, -1, 0, 1, 1, GL_LIGHT1);
spotLight.setSpotlight(30, 0.5, 0, 0, -1, 0);
Light yellowLight(0, 0, 0, 1, 0.8, 0.8, 0.6, 1, 0, 0, 0, 1, -400, 692, 0, 0, GL_LIGHT2);

float theta = 10.0; // for roll, yaw, pitch
float dist = 0.1;   // for sliding/moving along u, v, n
GLfloat bg_r = 0.5; // background color red
GLfloat bg_g = 0.5; // background color green
GLfloat bg_b = 0.5; // background color blue
GLfloat bg_a = 1.0; // background color alpha
GLfloat ex = 0.0;   // eye position x
GLfloat ey = 0.0;   // eye position y
GLfloat ez = 1.0;   // eye position z
GLfloat lx = 0.0;   // look point x
GLfloat ly = 0.0;   // look point y
GLfloat lz = 0.0;   // look point z
GLfloat ux = 0.0;   // up vector x
GLfloat uy = 1.0;   // up vector y
GLfloat uz = 0.0;   // up vector z
GLfloat leftPos = -0.25;
GLfloat rightPos = 0.25;
GLfloat bottomPos = -0.20;
GLfloat topPos = 0.20;
GLfloat nearClip = 0.2;
GLfloat farClip = 10.0;
Point eye(ex, ey, ez);
Point look(lx, ly, lz);
Vector up(ux, uy, uz);
Vector u, v, n;
Camera camera;
Color backgroundColor(bg_r, bg_g, bg_b);
int blockSize[8] = {1, 2, 4, 5, 10, 20, 50, 100};
int blockIndex = 0;
// define spheres and a cylinder
Object o1("sphere", 0.125, 0.125, -0.25, -1.0, 1.0, 0.0, 0.0);
Object o2("sphere", 0.375, 0.5, 0.5, -1.75, 0.0, 0.0, 1.0);
Object o3("sphere", 0.75, -0.5, 0.0, -2.5, 0.0, 1.0, 0.0);
Object o4("cylinder", 0.15, 0.5, 0.5, -0.25, -1.00, 0.0, 1.0, 1.0);
// use STL vector to store objects
vector<Object> objects;
RayCast raycaster;

void init()
{
    // set up lights
    glEnable(GL_LIGHTING);
    pointLight.on();
    spotLight.on();
    yellowLight.on();

    // add objects to the object list
    objects.push_back(o1);
    objects.push_back(o2);
    objects.push_back(o3);
    objects.push_back(o4);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, WIDTH, HEIGHT);
    camera.setShape(32.0, (GLfloat)WIDTH / HEIGHT, 0.2, 10.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(leftPos, rightPos, bottomPos, topPos, nearClip, farClip);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    camera.set(eye, look, up);
    raycaster.set(backgroundColor, WIDTH, HEIGHT, blockSize[blockIndex], camera);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // update the parameters for raycaster
    raycaster.set(backgroundColor, WIDTH, HEIGHT, blockSize[blockIndex], camera);
    // ray tracing and draw objects
    raycaster.RayTrace(objects);

    if (USEFREEIMAGE) saveImage();
    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case '1':
        camera.slide(0.0, 0.0, dist);
        break;
    case '5':
        camera.slide(0.0, 0.0, -dist);
        break;
    case '4':
        camera.slide(dist, 0.0, 0.0);
        break;
    case '6':
        camera.slide(-dist, 0.0, 0.0);
        break;
    case '8':
        camera.slide(0.0, dist, 0.0);
        break;
    case '2':
        camera.slide(0.0, -dist, 0.0);
        break;
    case 'A':
    case 'a':
        camera.yaw(-theta);
        break;
    case 'D':
    case 'd':
        camera.yaw(theta);
        break;
    case 'W':
    case 'w':
        camera.pitch(-theta);
        break;
    case 'S':
    case 's':
        camera.pitch(theta);
        break;
    case 'Q':
    case 'q':
        camera.roll(-theta);
        break;
    case 'E':
    case 'e':
        camera.roll(theta);
        break;
    // decrease blocksize to make the resolution of objects higher
    case '-':
        if (--blockIndex <= 0) blockIndex = 0;
        break;
    // increase blocksize to make the resolution of objects lower
    case '+':
        if (++blockIndex >= 8) blockIndex = 7;
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
    glutCreateWindow("COSC 5450 Project 3: RayCaster by Libao Jin");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
