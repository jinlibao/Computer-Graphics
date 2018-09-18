/**
 * paint.cpp
 * Copyright (C) 2018 Libao Jin
 * Email: <jinlibao@outlook.com>
 * Date: 09/09/2018
 * Distributed under terms of the MIT license.
 */

// C++ Libraries
#include <iostream>
#include <cmath>
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
    double angle;
    double aspect;
    double r;
    double g;
    double b;
    double a;
    bool drawState;
    bool deleteState;
    const char* title;
} glutWindow;

typedef struct {
    int x;
    int y;
    int button;
    int state;
} glutMouse;

typedef struct {
    double r;
    double g;
    double b;
    double a;
    double px;
} glutPen;

typedef struct {
    int left;
    int right;
    int bottom;
    int top;
    int edge;
} glutToolbar;

typedef struct {
    int x1;
    int y1;
    int x2;
    int y2;
} glutDeleteRect;

glutWindow window;
glutMouse mouse;
glutPen pen;
glutToolbar toolbar;
glutDeleteRect deleteRect;

void initFunc();
void createMenu();
void keyboardFunc(unsigned char key, int x, int y);
void specialFunc(int key, int x, int y);
void mouseFunc(int button, int state, int x, int y);
void motionFunc(int x, int y);
void passiveMotionFunc(int x, int y);
void reshapeFunc(int width, int height);
void displayFunc();
void menuFunc(int id);
void drawMSLogo(double x, double y);
void drawLine(int x1, int y1, int x2, int y2);
void drawTriangle(double x1, double y1, double s);
void drawSquare(double x, double y, double s);
void drawCircle(double ox, double y, double r);
void drawToolbar();
void drawDeleteRect(double x1, double y1, double x2, double y2);
void drawDeleteRectDotted(double x1, double y1, double x2, double y2);

int main(int argc, char* argv[]) {
    // initialize the parameters for window
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
    window.a = 1.0f;
    window.drawState = false;
    window.deleteState = false;

    // initialize the parameters for pen
    pen.r = 1.0f;
    pen.g = 0.0f;
    pen.b = 0.0f;
    pen.a = 1.0f;
    pen.px = 1.0f;

    // initialize the parameters for toolbar
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
    glutPassiveMotionFunc(passiveMotionFunc);
    glutDisplayFunc(displayFunc);
    createMenu();
    initFunc();
    // glutReshapeFunc(reshapeFunc);
    glutMainLoop();
    return 0;
}

void initFunc() {
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

void specialFunc(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_F9:
        case GLUT_KEY_DOWN:
            exit(0);
        default:
            break;
    }
}

void mouseFunc(int button, int state, int x, int y) {
    printf("Mouse x: %d, y: %d\n", x,  y);
    mouse.x = x;
    mouse.y = y;
    mouse.button = button;
    mouse.state = state;

    if (mouse.x >= 10 && mouse.x <= 30) {
        if (window.height - mouse.y >= 338 && window.height - mouse.y <= 342) {
            window.deleteState = false;
            window.drawState = true;
            pen.px = 4.0;
        }
        else if (window.height - mouse.y >= 310 && window.height - mouse.y <= 320) {
            window.deleteState = false;
            window.drawState = true;
            pen.px = 10.0;
        }
        else if (window.height - mouse.y >= 270 && window.height - mouse.y <= 290) {
            window.deleteState = false;
            window.drawState = true;
            pen.px = 20.0;
        }
        else if (window.height - mouse.y >= 230 && window.height - mouse.y <= 250) {
            window.deleteState = false;
            window.drawState = true;
            pen.r = 1.0f;
            pen.g = 0.0f;
            pen.b = 0.0f;
            pen.a = 1.0f;
        }
        else if (window.height - mouse.y >= 190 && window.height - mouse.y <= 210) {
            window.deleteState = false;
            window.drawState = true;
            pen.r = 0.0f;
            pen.g = 1.0f;
            pen.b = 0.0f;
            pen.a = 1.0f;
        }
        else if (window.height - mouse.y >= 150 && window.height - mouse.y <= 170) {
            window.deleteState = false;
            window.drawState = true;
            pen.r = 0.0f;
            pen.g = 0.0f;
            pen.b = 1.0f;
            pen.a = 1.0f;
        }
        else if (window.height - mouse.y >= 110 && window.height - mouse.y <= 130) {
            window.deleteState = true;
            window.drawState = false;
        }
    }

    if (window.deleteState) {
        if (mouse.button == GLUT_LEFT_BUTTON && mouse.state == GLUT_DOWN) {
            deleteRect.x1 = mouse.x;
            deleteRect.y1 = window.height - mouse.y;
        }
        else if (mouse.button == GLUT_LEFT_BUTTON && mouse.state == GLUT_UP) {
            deleteRect.x2 = mouse.x;
            deleteRect.y2 = window.height - mouse.y;
            drawDeleteRect(deleteRect.x1, deleteRect.y1, deleteRect.x2, deleteRect.y2);
        }
    }

}

void motionFunc(int x, int y) {
    printf("Motion x: %d, y: %d\n", x,  y);
    if (mouse.state == GLUT_DOWN && window.drawState) {
        if (mouse.button == GLUT_LEFT_BUTTON) {
            drawLine(mouse.x, window.height - mouse.y, x, window.height - y);
        }
    }
    mouse.x = x;
    mouse.y = y;
    if (window.deleteState) {
        if (mouse.state == GLUT_DOWN && mouse.button == GLUT_LEFT_BUTTON) {
            deleteRect.x2 = mouse.x;
            deleteRect.y2 = window.height - mouse.y;
            drawDeleteRectDotted(deleteRect.x1, deleteRect.y1, deleteRect.x2, deleteRect.y2);
        }
    }
}

void passiveMotionFunc(int x, int y) {
    printf("Passive Motion x: %d, y: %d\n", x,  y);
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

    glFlush();
}

void drawLine(int x1, int y1, int x2, int y2) {
    glColor4f(pen.r, pen.g, pen.b, 1.0f);
    glLineWidth(pen.px);
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
    const int N = 32;
    double theta = 8 * atan(1) / N;

    glBegin(GL_POLYGON);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glVertex2f(toolbar.left + toolbar.edge, toolbar.bottom + toolbar.edge);
    glVertex2f(toolbar.left + toolbar.edge, toolbar.top - toolbar.edge);
    glVertex2f(toolbar.right - toolbar.edge, toolbar.top - toolbar.edge);
    glVertex2f(toolbar.right - toolbar.edge, toolbar.bottom + toolbar.edge);
    glEnd();

    // brush radius 5px
    // 10 <= x <= 30
    // 338 <= y <= 342
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

    // brush radius 5px
    // 10 <= x <= 30
    // 310 <= y <= 320
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

    // brush radius 10px
    // 10 <= x <= 30
    // 270 <= y <= 290
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

    // red color plate
    // 10 <= x <= 30
    // 230 <= y <= 250
    glBegin(GL_POLYGON);
    x = 20;
    y = window.height - 120;
    glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
    glVertex2f(x - 10, y - 10);
    glVertex2f(x - 10, y + 10);
    glVertex2f(x + 10, y + 10);
    glVertex2f(x + 10, y - 10);
    glEnd();

    // green color plate
    // 10 <= x <= 30
    // 190 <= y <= 210
    glBegin(GL_POLYGON);
    x = 20;
    y = window.height - 160;
    glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
    glVertex2f(x - 10, y - 10);
    glVertex2f(x - 10, y + 10);
    glVertex2f(x + 10, y + 10);
    glVertex2f(x + 10, y - 10);
    glEnd();

    // blue color plate
    // 10 <= x <= 30
    // 150 <= y <= 170
    glBegin(GL_POLYGON);
    x = 20;
    y = window.height - 200;
    glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
    glVertex2f(x - 10, y - 10);
    glVertex2f(x - 10, y + 10);
    glVertex2f(x + 10, y + 10);
    glVertex2f(x + 10, y - 10);
    glEnd();

    // delete rectangle
    // 10 <= x <= 30
    // 110 <= y <= 130
    x = 20;
    y = window.height - 240;
    glLineWidth(1.0);
    glColor4f(1.0f, 0.0f, 1.0f, 1.0f);
    glLineStipple(1, 0xAAAA);
    glEnable(GL_LINE_STIPPLE);
    glBegin(GL_LINE_LOOP);
    glVertex2f(x - 10, y - 10);
    glVertex2f(x - 10, y + 10);
    glVertex2f(x + 10, y + 10);
    glVertex2f(x + 10, y - 10);
    glEnd();
    glDisable(GL_LINE_STIPPLE);

    glFlush();
}

void drawDeleteRect(double x1, double y1, double x2, double y2) {
    glColor4f(window.r, window.g, window.b, 1.0f);
    glBegin(GL_POLYGON);
        glVertex2f(x1, y1);
        glVertex2f(x2, y1);
        glVertex2f(x2, y2);
        glVertex2f(x1, y2);
    glEnd();
    glFlush();
}

void drawDeleteRectDotted(double x1, double y1, double x2, double y2) {
    // References:
    // http://3dengine.org/Drawing_dotted_lines_(OpenGL)
    // http://www.opengl.org.ru/docs/pg/0204.html

    glPushMatrix();
    glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
    glLineWidth(1.0);
    // glPushAttrib(GL_ENABLE_BIT);
    glLineStipple(1, 0xAAAA);
    glEnable(GL_LINE_STIPPLE);
    // glColor4f(window.r, window.g, window.b, 1.0f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(x1, y1);
        glVertex2f(x2, y1);
        glVertex2f(x2, y2);
        glVertex2f(x1, y2);
    glEnd();
    // glPopAttrib();
    glDisable(GL_LINE_STIPPLE);
    glFlush();
    glPopMatrix();
}

void createMenu() {
    glutCreateMenu(menuFunc);
    glutAddMenuEntry("Drawing Mode", 6);
    glutAddMenuEntry("Exit Drawing Mode", 14);
    glutAddMenuEntry("Draw Microsoft Logo", 3);
    glutAddMenuEntry("Draw a circle", 15);
    glutAddMenuEntry("Draw a square", 16);
    glutAddMenuEntry("Draw a triangle", 17);
    glutAddMenuEntry("Erase", 7);
    glutAddMenuEntry("Delete Mode", 18);
    glutAddMenuEntry("Exit Delete Mode", 19);
    glutAddMenuEntry("Brush Size 4px", 8);
    glutAddMenuEntry("Brush Size 10px", 9);
    glutAddMenuEntry("Brush Size 20px", 10);
    glutAddMenuEntry("Brush Color Red", 11);
    glutAddMenuEntry("Brush Color Green", 12);
    glutAddMenuEntry("Brush Color Blue", 13);
    glutAddMenuEntry("Clear Screen", 4);
    glutAddMenuEntry("Full Screen", 1);
    glutAddMenuEntry("Exit Full Screen", 2);
    glutAddMenuEntry("Exit Painter App", 5);
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
            window.deleteState = false;
            window.drawState = true;
            glColor3f(1.0f, 0.0f, 0.0f);
            glLineWidth(4.0);
            break;
        case 7:
            window.deleteState = false;
            window.drawState = true;
            pen.r = window.r;
            pen.g = window.g;
            pen.b = window.b;
            pen.a = window.a;
            pen.px = 20.0;
            break;
        case 8:
            glLineWidth(4.0);
            break;
        case 9:
            glLineWidth(10.0);
            break;
        case 10:
            glLineWidth(20.0);
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
            drawCircle(mouse.x, window.height - mouse.y, 25);
            break;
        case 16:
            drawSquare(mouse.x, window.height - mouse.y, 50);
            break;
        case 17:
            drawTriangle(mouse.x, window.height - mouse.y, 50);
            break;
        case 18:
            window.drawState = false;
            window.deleteState = true;
            glColor4f(window.r, window.g, window.b, 1.0f);
            break;
        case 19:
            window.drawState = false;
            window.deleteState = false;
        default:
            break;
    }
}
