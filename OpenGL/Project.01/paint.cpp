/**
 * paint.cpp
 * Copyright (C) 2018 Libao Jin
 * Email: <jinlibao@outlook.com>
 * Date: 09/09/2018
 * Distributed under terms of the MIT license.
 */

// C++ Libraries
#include <iostream>
// OpenGL Libraries
#ifdef __APPLE__
#include <GL/glut.h>
// #include <GLUT/glut.h>
#include <OpenGL/glu.h>
#include <OpenGL/gl.h>
#else
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#endif

#include <cmath>

using namespace std;

typedef struct {
    int id;
    int x;
    int y;
    int near;
    int far;
    int old_width;
    int old_height;
    int width;
    int height;
    float angle;
    float aspect;
    float r;
    float g;
    float b;
    bool drawState;
    const char* title;
} glutWindow;

typedef struct {
    int x;
    int y;
    int button;
    int state;
} glutMouse;

typedef struct {
    float r;
    float g;
    float b;
} glutPen;

typedef struct {
    int left;
    int right;
    int bottom;
    int top;
    int edge;
} glutToolbar;

glutWindow window;
glutMouse mouse;
glutToolbar toolbar;

void initFunc();
void createMenu();
void keyboardFunc(unsigned char key, int x, int y);
void specialFunc(int key, int x, int y);
void mouseFunc(int button, int state, int x, int y);
void motionFunc(int x, int y);
void reshapeFunc(int width, int height);
void displayFunc();
// void subWindowDisplayFunc();
void menuFunc(int id);
void drawMSLogo(double x, double y);
void drawLine(int x1, int y1, int x2, int y2);
void drawTriangle(double x1, double y1, double s);
void drawSquare(double x, double y, double s);
void drawCircle(double ox, double y, double r);
void drawToolbar();

int main(int argc, char* argv[]) {
    window.x = 0;
    window.y = 0;
    window.width = 640;
    window.height = 360;
    window.near = 1.0f;
    window.far = 30.0f;
    window.angle = 0;
    window.aspect = (float) window.width / window.height;
    window.title = "Painter App by Libao Jin";
    window.r = 0.3f;
    window.g = 0.3f;
    window.b = 0.3f;
    window.drawState = false;

    toolbar.left = 0;
    toolbar.bottom = 0;
    toolbar.right = 40;
    toolbar.top = 360;
    toolbar.edge = 5;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(window.width, window.height);
    glutInitWindowPosition(window.x, window.y);
    window.id = glutCreateWindow(window.title);
    glutKeyboardFunc(keyboardFunc);
    glutSpecialFunc(specialFunc);
    glutMouseFunc(mouseFunc);
    glutMotionFunc(motionFunc);
    glutDisplayFunc(displayFunc);
    createMenu();
    initFunc();
    // glutReshapeFunc(reshapeFunc);
    glutMainLoop();
    return 0;
}

void initFunc() {
    // glShadeModel(GL_SMOOTH);
    // glClearDepth(1.0f);
    // glEnable(GL_DEPTH_TEST);
    // glDepthFunc(GL_LEQUAL);
    // glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(window.r, window.g, window.b, 1.0f);
    glColor4f(window.r, window.g, window.b, 1.0f);
    glFlush();
}

void displayFunc() {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(window.r, window.g, window.b, 1.0f);

    // draw toolbar
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, 140, 360);
    gluOrtho2D(0.0, 140.0, 0.0, 360.0);
    drawToolbar();
    glLoadIdentity();

    // set the viewport for drawing
    glViewport(40, 0, 600, 360);
    gluOrtho2D(40.0, 640.0, 0.0, 360.0);
    glFlush();
}

void keyboardFunc(unsigned char key, int x, int y) {
    switch (key) {
        case 'Q':
        case 'q':
            exit(0);
            break;
        default:
            break;
    }
    if (glutGetModifiers() & GLUT_ACTIVE_CTRL && key == 'Q')  // Only be called while a keyboard, speical, or mouse callback is being handled
        exit(0);
}

void mouseFunc(int button, int state, int x, int y) {
    mouse.x = x;
    mouse.y = y;
    mouse.button = button;
    mouse.state = state;
}

void specialFunc(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_F9:
        case GLUT_KEY_DOWN:
            exit(0);
        default:
            break;
    }
}

void motionFunc(int x, int y) {
    if (mouse.state == GLUT_DOWN && window.drawState) {
        if (mouse.button == GLUT_LEFT_BUTTON) {
            drawLine(mouse.x, window.height - mouse.y, x, window.height - y);
        }
    }
    mouse.x = x;
    mouse.y = y;
}

void reshapeFunc(int width, int height) {
    window.old_width = window.width;
    window.old_height = window.height;
    window.width = width;
    window.height = height;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // glViewport(window.x, window.y, window.width, window.height);
    if (window.aspect < window.width / window.height) {
        glViewport(window.x, window.y, (GLdouble) window.height * window.aspect, window.height);
        gluOrtho2D(0.0, (GLdouble) window.height * window.aspect, 0.0, window.height);
    }
    else {
        glViewport(window.x, window.y, window.width, (GLdouble) window.width / window.aspect);
        gluOrtho2D(0.0, window.width, 0.0, (GLdouble) window.width / window.aspect);
    }
    window.width = width;
    window.height = height;
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glFlush();
    glutPostRedisplay();
}

void drawMSLogo(double x, double y) {
    const double sideLength = 25.0;
    const double space = 0.1 * sideLength;
    // Microsoft Logo
    glColor4f(.8789, .3711, .21875, 1);
    glBegin(GL_QUADS);
    glVertex2f(.0 + x, .0 + y);
    glVertex2f(sideLength + x, .0 + y);
    glVertex2f(sideLength + x, sideLength + y);
    glVertex2f(0 + x, sideLength + y);
    glEnd();

    glColor4f(.5547, .7305, .2305, 1);
    glBegin(GL_QUADS);
    glVertex2f(sideLength + space + x, .0 + y);
    glVertex2f(2 * sideLength + space + x, .0 + y);
    glVertex2f(2 * sideLength + space + x, sideLength + y);
    glVertex2f(sideLength + space + x, sideLength + y);
    glEnd();

    glColor4f(.9570, .7383, .2695, 1);
    glBegin(GL_QUADS);
    glVertex2f(sideLength + space + x, sideLength + space + y);
    glVertex2f(2 * sideLength + space + x, sideLength + space + y);
    glVertex2f(2 * sideLength + space + x, 2 * sideLength + space + y);
    glVertex2f(sideLength + space + x, 2 * sideLength + space + y);
    glEnd();

    glColor4f(.2930, .6406, .9141, 1);
    glBegin(GL_QUADS);
    glVertex2f(0 + x, sideLength + space + y);
    glVertex2f(sideLength + x, sideLength + space + y);
    glVertex2f(sideLength + x, 2 * sideLength + space + y);
    glVertex2f(0 + x, 2 * sideLength + space + y);
    glEnd();

    glColor4f(window.r, window.g, window.b, 1.0f);
    window.drawState = false;
    glFlush();
}

void drawLine(int x1, int y1, int x2, int y2) {
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
    glFlush();
}

void drawTriangle(double x, double y, double s) {
    glColor4f(0.0f, 1.0f, 1.0f, 1.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(x, y);
    glVertex2f(x + s, y);
    glVertex2f(x + s / 2, y + sqrt(3) / 2 * s);
    glEnd();
    glFlush();
}

void drawSquare(double x, double y, double s) {
    glColor4f(1.0f, 0.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + s, y);
    glVertex2f(x + s, y + s);
    glVertex2f(x, y + s);
    glEnd();
    glFlush();
}

void drawCircle(double x, double y, double r) {
    glColor4f(1.0f, 1.0f, 0.0f, 1.0f);
    const int N = 512;
    double theta = 8 * atan(1) / N;
    double x0 = r;
    double y0 = 0;
    glBegin(GL_POLYGON);
    // glBegin(GL_LINE_LOOP);
    for (int i = 0; i < N; ++i) {
        double nx = x0 * cos(i * theta) - y0 * sin(i * theta);
        double ny = x0 * sin(i * theta) + y0 * cos(i * theta);
        glVertex2f(x + nx, y + ny);
    }
    glEnd();
    glFlush();
}

void drawToolbar() {

    double x, y, r;
    const int N = 512;
    double theta = 8 * atan(1) / N;

    glBegin(GL_POLYGON);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glVertex2f(toolbar.left + toolbar.edge, toolbar.bottom + toolbar.edge);
    glVertex2f(toolbar.left + toolbar.edge, toolbar.top - toolbar.edge);
    glVertex2f(toolbar.right - toolbar.edge, toolbar.top - toolbar.edge);
    glVertex2f(toolbar.right - toolbar.edge, toolbar.bottom + toolbar.edge);
    glEnd();

    glBegin(GL_POLYGON);
    glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
    x = 20;
    y = window.height - 20;
    r = 2;
    for (int i = 0; i < N; ++i) {
        double nx = r * cos(i * theta);
        double ny = r * sin(i * theta);
        glVertex2f(x + nx, y + ny);
    }
    glEnd();

    glBegin(GL_POLYGON);
    glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
    x = 20;
    y = window.height - 45;
    r = 5;
    for (int i = 0; i < N; ++i) {
        double nx = r * cos(i * theta);
        double ny = r * sin(i * theta);
        glVertex2f(x + nx, y + ny);
    }
    glEnd();

    glBegin(GL_POLYGON);
    glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
    x = 20;
    y = window.height - 80;
    r = 10;
    for (int i = 0; i < N; ++i) {
        double nx = r * cos(i * theta);
        double ny = r * sin(i * theta);
        glVertex2f(x + nx, y + ny);
    }
    glEnd();

    glBegin(GL_POLYGON);
    x = 20;
    y = window.height - 120;
    glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
    glVertex2f(x - 10, y - 10);
    glVertex2f(x - 10, y + 10);
    glVertex2f(x + 10, y + 10);
    glVertex2f(x + 10, y - 10);
    glEnd();

    glBegin(GL_POLYGON);
    x = 20;
    y = window.height - 160;
    glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
    glVertex2f(x - 10, y - 10);
    glVertex2f(x - 10, y + 10);
    glVertex2f(x + 10, y + 10);
    glVertex2f(x + 10, y - 10);
    glEnd();

    glBegin(GL_POLYGON);
    x = 20;
    y = window.height - 200;
    glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
    glVertex2f(x - 10, y - 10);
    glVertex2f(x - 10, y + 10);
    glVertex2f(x + 10, y + 10);
    glVertex2f(x + 10, y - 10);
    glEnd();

    glFlush();
}

void createMenu() {
    glutCreateMenu(menuFunc);
    glutAddMenuEntry("Full Screen", 1);
    glutAddMenuEntry("Exit Full Screen", 2);
    glutAddMenuEntry("Draw Microsoft Logo", 3);
    glutAddMenuEntry("Draw a circle", 15);
    glutAddMenuEntry("Draw a square", 16);
    glutAddMenuEntry("Draw a triangle", 17);
    glutAddMenuEntry("Clear Screen", 4);
    glutAddMenuEntry("Exit", 5);
    glutAddMenuEntry("Draw", 6);
    glutAddMenuEntry("Erase", 7);
    glutAddMenuEntry("Brush Size 1px", 8);
    glutAddMenuEntry("Brush Size 5px", 9);
    glutAddMenuEntry("Brush Size 10px", 10);
    glutAddMenuEntry("Brush Color Red", 11);
    glutAddMenuEntry("Brush Color Green", 12);
    glutAddMenuEntry("Brush Color Blue", 13);
    glutAddMenuEntry("Exit Drawing Mode", 14);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void menuFunc(int id) {
    switch (id) {
        case 1:
            glutFullScreen();
            // glutPostRedisplay();
            // glFlush();
            break;
        case 2:
            glutPositionWindow(window.x, window.y);
            glutReshapeWindow(window.old_width, window.old_height);
            // glMatrixMode(GL_PROJECTION);
            // glLoadIdentity();
            // if (window.aspect < window.width / window.height) {
            //     glViewport(window.x, window.y, (GLdouble) window.height * window.aspect, window.height);
            //     gluOrtho2D(0.0, (GLdouble) window.height * window.aspect, 0.0, window.height);
            // }
            // else {
            //     glViewport(window.x, window.y, window.width, (GLdouble) window.width / window.aspect);
            //     gluOrtho2D(0.0, window.width, 0.0, (GLdouble) window.width / window.aspect);
            // }
            // glutPostRedisplay();
            break;
        case 3:
            drawMSLogo(mouse.x, window.height - mouse.y);
            break;
        case 4:
            glClear(GL_COLOR_BUFFER_BIT);
            glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
            glFlush();
            glutPostRedisplay();
            break;
        case 5:
            glutDestroyWindow(window.id);
            exit(0);
            break;
        case 6:
            window.drawState = true;
            glColor3f(1.0f, 0.0f, 0.0f);
            glLineWidth(1.0);
            break;
        case 7:
            window.drawState = true;
            glColor3f(window.r, window.g, window.b);
            glLineWidth(20.0);
            break;
        case 8:
            glLineWidth(1.0);
            break;
        case 9:
            glLineWidth(5.0);
            break;
        case 10:
            glLineWidth(10.0);
            break;
        case 11:
            glColor3f(1.0f, 0.0f, 0.0f);
            break;
        case 12:
            glColor3f(0.0f, 1.0f, 0.0f);
            break;
        case 13:
            glColor3f(0.0f, 0.0f, 1.0f);
            break;
        case 14:
            glColor3f(window.r, window.g, window.b);
            window.drawState = false;
            glColor3f(0.0f, 0.0f, 1.0f);
            break;
        case 15:
            drawCircle(mouse.x, window.height - mouse.y, 50);
            break;
        case 16:
            drawSquare(mouse.x, window.height - mouse.y, 100);
            break;
        case 17:
            drawTriangle(mouse.x, window.height - mouse.y, 50);
            break;
        default:
            break;
    }
}
