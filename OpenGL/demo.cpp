/**
 * demo.cpp
 * Copyright (C) 2018 Libao Jin
 * Email: <jinlibao@outlook.com>
 * Date: 09/08/2018
 * Distributed under terms of the MIT license.
 */

#include <iostream>
// OpenGL libraries
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GL/glut.h>
#include <GLKit/GLKMatrix4.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GLKit/GLKMatrix4.h>
#endif

using namespace std;

const int KEY_ESCAPE = 27;

typedef struct {
    int positionX;
    int positionY;
    int width;
    int height;
    const char* title;

    float fieldOfViewAngle;
    float zNear;
    float zFar;
} glutWindow;

glutWindow win;

void display();
void init();
void keyboard(unsigned char key, int mousePositionX, int mousePositionY);

int main(int argc, char* argv[]) {
    // Set window values
    win.positionX = 0;
    win.positionY = 0;
    win.width = 500;
    win.height = 500;
    win.title = "Computer Graphics";
    win.fieldOfViewAngle = 45.0f;
    win.zNear = 1.0f;
    win.zFar = 500.0f;

    int mode = GLUT_SINGLE | GLUT_RGB;
    glutInit(&argc, argv);
    glutInitDisplayMode(mode);
    glutInitWindowSize(win.width, win.height);
    glutInitWindowPosition(win.positionX, win.positionY);
    glutCreateWindow(win.title);
    // init();
    // Register callback function for display event
    glutDisplayFunc(display);
    // Register Idle Function
    glutIdleFunc(display);
    // Register Keyboard Handler
    glutKeyboardFunc(keyboard);
    // glutMouseFunc();
    // glutMotionFunc();
    // Enter the event loop
    glutMainLoop();
    return 0;
}

void init() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // Set the viewport
    glViewport(win.positionX, win.positionY, win.width, win.height);
    // gluOrtho2D(0, 640.0, 0, 480.0);
    GLKMatrix4 orthoMat = GLKMatrix4MakeOrtho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
    GLfloat aspect = (GLfloat) win.width / win.height;
    // Set up a perspective projection matrix
    // gluPerspective(win.field_of_view_angle, aspect, win.z_near, win.z_far);
    glMultMatrixf(GLKMatrix4MakePerspective(win.fieldOfViewAngle, aspect, win.zNear, win.zFar).m);
    // Specify which matrix is the current matrix
    glMatrixMode(GL_MODELVIEW);
    glShadeModel(GL_SMOOTH);
    // Specify the clear value for the depth buffer
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    // Specify implementation-specific hints
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    // Specify clear values for the color buffers
    glClearColor(.3, .3, .3, 1.0);
}

void keyboard(unsigned char key, int mousePositionX, int mousePositionY) {
    switch (key) {
        case KEY_ESCAPE:
            exit (0);
            break;
        default:
            break;
    }
}

void display() {
    // Clear Screen and Depth Buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // glLoadIdentity();
    // glTranslatef(0.0f, 0.0f, -2.0f);

    // One green line
    glColor4f(0, 1, 0, .5);
    glBegin(GL_LINES);
    glVertex2f(.0, .0);
    glVertex2f(1.0, 1.0);
    glEnd();

    // Microsoft Logo
    glColor4f(.8789, .3711, .21875, 1);
    glBegin(GL_QUADS);
    glVertex2f(.0, .0);
    glVertex2f(-.1, .0);
    glVertex2f(-.1, .1);
    glVertex2f(.0, .1);
    glEnd();

    glColor4f(.5547, .7305, .2305, 1);
    glBegin(GL_QUADS);
    glVertex2f(.0, .0);
    glVertex2f(.1, .0);
    glVertex2f(.1, .1);
    glVertex2f(.0, .1);
    glEnd();

    glColor4f(.9570, .7383, .2695, 1);
    glBegin(GL_QUADS);
    glVertex2f(.0, .0);
    glVertex2f(.1, .0);
    glVertex2f(.1, -.1);
    glVertex2f(.0, -.1);
    glEnd();

    glColor4f(.2930, .6406, .9141, 1);
    glBegin(GL_QUADS);
    glVertex2f(.0, .0);
    glVertex2f(-.1, .0);
    glVertex2f(-.1, -.1);
    glVertex2f(.0, -.1);
    glEnd();

    // Square frame
    glColor4f(0, 1, 1, .5);
    // glBegin(GL_LINE_STRIP);
    glBegin(GL_LINE_LOOP);
    glVertex2f(.1, .1);
    glVertex2f(.1, .25);
    glVertex2f(.25, .25);
    glVertex2f(.25, .1);
    glEnd();

    // Quadrilateral (Square)
    glColor4f(1, 0, 1, .5);
    glBegin(GL_QUADS);
    glVertex2f(.25, .25);
    glVertex2f(.25, .5);
    glVertex2f(.5, .5);
    glVertex2f(.5, .25);
    glEnd();

    // Polygon (Square)
    glColor4f(1, 1, 0, .5);
    glBegin(GL_POLYGON);
    glVertex2f(.5, .5);
    glVertex2f(.5, 1.0);
    glVertex2f(1.0, 1.0);
    glVertex2f(1.0, .5);
    glEnd();

    // Four points
    glColor4f(1, 0, 0, .5);
    glBegin(GL_POINTS);
    glVertex2f(.2, .2);
    glVertex2f(.2, -.2);
    glVertex2f(-.2, .2);
    glVertex2f(-.2, -.2);
    glEnd();

    // One triangle
    glColor4f(0, 0, 1, .5);
    glBegin(GL_TRIANGLES);
    glVertex2f(-.25, -.05);
    glVertex2f(-.35, -.05);
    glVertex2f(-.30, .05);
    glEnd();

    // Two triangles with color gradient
    glBegin(GL_TRIANGLE_STRIP);
    glColor4f(1.0, 0.0, 0.0, 0.5);
    glVertex2f(-1.0, -.75);
    glColor4f(0.0, 0.0, 1.0, 0.5);
    glVertex2f(-.75, -1.0);
    glColor4f(0.0, 1.0, 0.0, 0.5);
    glVertex2f(-0.75, -0.5);
    glColor4f(1.0, 1.0, 0.0, 0.5);
    glVertex2f(-0.5, -0.75);
    glEnd();

    glFlush();
    // glutSwapBuffers();
}
