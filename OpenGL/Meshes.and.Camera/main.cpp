// Libao Jin
// ljin1@uwyo.edu
// #define X11 X11
#if defined __APPLE__ && !defined X11
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

#include "camera.h"
// #include "light.h"
// #include "material.h"
#include "matrix.h"
#include "mesh.h"
#include <FreeImage.h>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>

using namespace std;

GLint const WIDTH = 640, HEIGHT = 480;
GLint BitsPerPixel = 32;
GLint modeSwitch = 0; // 1: OpenGL, 0: Camera Class

// Material libertyMaterial(0.0, 0.0, 0.1, 1.0, 0.195441, 0.263741, 0.2537, 1.0,
//                          0.0237312, 0.0522111, 0.0793909, 1.0, 0.2, 0.2, 0.2,
//                          1.0, 50.0);
// Material surfaceMaterial(0.0, 0.0, 0.0, 1.0, 0.8, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0,
//                          1.0, 0.2, 0.2, 0.2, 1.0);
// Material glutWireOjectMaterial(0.0, 0.0, 0.0, 1.0, 0.8, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0,
//                          1.0, 0.2, 0.2, 0.2, 1.0);
// Material mugMaterial(0.0, 0.0, 0.0, 1.0, 0.8, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0,
//                          1.0, 0.2, 0.2, 0.2, 1.0);

GLfloat lib_mat_ambient[4] = {0.0, 0.0, 0.1, 1.0};
GLfloat lib_mat_diffuse[4] = {0.195441, 0.263741, 0.2537, 1.0};
GLfloat lib_mat_specular[4] = {0.0237312, 0.0522111, 0.0793909, 1.0};
GLfloat lib_mat_emission[4] = {0.2, 0.2, 0.2, 1.0};
GLfloat lib_mat_shininess = 50.0;

GLfloat mat_ambient[4] = {0.0, 0.0, 0.0, 1.0};
GLfloat mat_diffuse[4] = {0.8, 0.0, 0.0, 1.0};
GLfloat mat_specular[4] = {1.0, 1.0, 1.0, 1.0};
GLfloat mat_emission[4] = {0.2, 0.2, 0.2, 1.0};
GLfloat mat_shininess = 20.0;

GLfloat light_ambient[] = {0.2, 0.2, 0.2, 1.0};
GLfloat light_diffuse[] = {1.0, 0.0, 0.0, 1.0};
GLfloat light_specular[] = {1.0, 1.0, 1.0, 1.0};
GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0};

GLfloat bg_r = 1.0;
GLfloat bg_g = 1.0;
GLfloat bg_b = 1.0;
GLfloat bg_a = 1.0;

GLfloat ex = 100.0;
GLfloat ey = 100.0;
GLfloat ez = 100.0;
GLfloat lx = 0.0;
GLfloat ly = 0.0;
GLfloat lz = 0.0;
GLfloat ux = 0.0;
GLfloat uy = 1.0;
GLfloat uz = 0.0;
Point eye(ex, ey, ez);
Point look(lx, ly, lz);
Vector up(ux, uy, uz);

float theta = 10.0;
float dist = 5.0;
int frameNumber = 1;
int row = 3, col = 3, layers = 3;
Camera camera;
Mesh mug, liberty, surfaceOfRevolution;

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

    glPushMatrix();
    glTranslated(40.0, 20.0, 0.0);
    glutWireTorus(2.0, 5.0, 20, 20);
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

    glPushMatrix();
    glTranslated(0.0, 20.0, 20.0);
    glutWireCone(5.0, 10.0, 20, 20);
    glPopMatrix();

    glPushMatrix();
    glTranslated(0.0, 40.0, 20.0);
    glutWireTeapot(10.0);
    glPopMatrix();
}

void drawWireframeObjects()
{
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, lib_mat_ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, lib_mat_diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, lib_mat_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, lib_mat_emission);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, lib_mat_shininess);
    // glShadeModel(GL_SMOOTH);
    GLfloat light1_pos[] = {1.0, 1.0, 0.0, 0.0};
    glLightfv(GL_LIGHT1, GL_AMBIENT, lib_mat_ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lib_mat_diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, lib_mat_specular);
    glLightfv(GL_LIGHT1, GL_POSITION, light1_pos);
    glEnable(GL_LIGHT1);

    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            for (int k = 0; k < layers; ++k) {
                glPushMatrix();
                glTranslated(i * 90.0 - 50.0, j * 90.0 - 50., k * 90.0 - 50.);
                glScaled(50.0, 50.0, 50.0);
                glRotated(10 * (i + j + k), i % 3 == 0, j % 3 == 0, k % 3 == 0);
                liberty.draw(1);
                glPopMatrix();
            }
        }
    }

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, mat_emission);
    // glShadeModel(GL_SMOOTH);

    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            for (int k = 0; k < layers; ++k) {
                glPushMatrix();
                glTranslated(i * -160.0, j * -160.0, k * -160.0);
                glScaled(10.0, 10.0, 10.0);
                glRotated(10 * (i + j + k), i % 3 == 0, j % 3 == 0, k % 3 == 0);
                mug.draw(1);
                glPopMatrix();
            }
        }
    }

    glPushMatrix();
    glTranslated(0.0, 20.0, 40.0);
    glScaled(5.0, 5.0, 5.0);
    surfaceOfRevolution.draw(1);
    glPopMatrix();
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
    liberty.readObj("./obj/liberty.statue.simplified.obj", 4);
    mug.readObj("./obj/Mug.obj", 3);
    surfaceOfRevolution.makeSurfaceMesh();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(bg_r, bg_g, bg_b, bg_a);
    // Set up camera using Camera class
    glViewport(0, 0, WIDTH, HEIGHT);
    camera.setShape(90.0, (GLfloat)WIDTH / HEIGHT, 1.0, 1000.0);
    camera.set(eye, look, up);
    // Set up lights
    glEnable(GL_LIGHTING);
    // Enable a single OpenGL light.
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glEnable(GL_LIGHT0);
    // Use depth buffering for hidden surface elimination.
    glEnable(GL_DEPTH_TEST);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(bg_r, bg_g, bg_b, bg_a);
    glColor4f(1.0, 0.0, 1.0, 1.0);

    drawWireframeObjects();
    drawGlutObjects();
    drawBox();

    saveImage();
    glFlush();
    glutSwapBuffers();
}

// void moveAlongU(float dist) {
//     look.set(camera.GetLook());
//     eye.set(camera.GetEye());
//     Vector u(camera.GetU());
//     eye.set(eye + u * dist);
//     look.set(look + u * dist);
//     gluLookAt(eye.x, eye.y, eye.z, look.x, look.y, look.z, up.x, up.y, up.z);
// }
//
// void moveAlongV(float dist) {
//     look.set(camera.GetLook());
//     eye.set(camera.GetEye());
//     Vector v(camera.GetU());
//     eye.set(eye + v * dist);
//     look.set(look + v * dist);
//     gluLookAt(eye.x, eye.y, eye.z, look.x, look.y, look.z, up.x, up.y, up.z);
// }
//
// void moveAlongN(float dist) {
//     look.set(camera.GetLook());
//     eye.set(camera.GetEye());
//     Vector n(camera.GetN());
//     eye.set(eye + n * dist);
//     look.set(look + n * dist);
//     gluLookAt(eye.x, eye.y, eye.z, look.x, look.y, look.z, up.x, up.y, up.z);
// }
//
// void yaw(float theta) {
//     eye.set(camera.GetEye());
//     Vector v(camera.GetV());
//     glPushMatrix();
//     glTranslatef(-eye.x, -eye.y, -eye.z);
//     glRotatef(theta, v.x, v.y, v.z);
//     glTranslatef(eye.x, -eye.y, eye.z);
//     glPopMatrix();
// }
//
// void roll(float theta) {
//     Vector n(camera.GetN());
//     glRotatef(theta, n.x, n.y, n.z);
// }
//
// void pitch(float theta) {
//     Vector u(camera.GetU());
//     glRotatef(theta, u.x, u.y, u.z);
// }

void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case '1':
        printf("Camera moves backward along n vector.\n");
        camera.moveAlongN(dist);
        break;
    case '5':
        printf("Camera moves forward along n vector.\n");
        camera.moveAlongN(-dist);
        break;
    case '4':
        printf("Camera moves left along u vector.\n");
        camera.moveAlongU(-dist);
        break;
    case '6':
        printf("Camera moves right along u vector.\n");
        camera.moveAlongU(dist);
        break;
    case '8':
        printf("Camera moves up along v vector.\n");
        camera.moveAlongV(dist);
        break;
    case '2':
        printf("Camera moves down along v vector.\n");
        camera.moveAlongV(-dist);
        break;
    case 'A':
    case 'a':
        printf("Left yaw\n");
        // modeSwitch == 0 ? camera.yaw(-theta) : yaw(-theta);
        camera.yaw(-theta);
        break;
    case 'D':
    case 'd':
        printf("Right yaw\n");
        // modeSwitch == 0 ? camera.yaw(theta) : yaw(theta);
        camera.yaw(theta);
        break;
    case 'W':
    case 'w':
        printf("Up pitch\n");
        camera.pitch(-theta);
        break;
    case 'S':
    case 's':
        printf("Down pitch\n");
        camera.pitch(theta);
        break;
    case 'Q':
    case 'q':
        printf("Left roll\n");
        camera.roll(-theta);
        break;
    case 'E':
    case 'e':
        camera.roll(theta);
        printf("Right roll\n");
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
