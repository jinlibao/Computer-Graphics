#include <string>
#include <iostream>
#include <fstream>
#include <strstream>
using namespace std;

// #include <windows.h> //change if using xWindows
#include <assert.h>
#include <math.h>
#include <stdlib.h>
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

#include "Meshclass.h"

//<<<<<<<<<<<<<<<<<<< axis >>>>>>>>>>>>>>
void axis(double length)
{ // draw a z-axis, with cone at end
    glPushMatrix();
    glBegin(GL_LINES);
    glVertex3d(0, 0, 0); glVertex3d(0, 0, length); // along the z-axis
    glEnd();
    glTranslated(0, 0, length - 0.2);
    glutWireCone(0.04, 0.2, 12, 9);
    glPopMatrix();
}
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<< displayWire >>>>>>>>>>>>>>>>>>>>>>
void displayWire(void)
{
    Mesh * M;
    M = new Mesh();
    glMatrixMode(GL_PROJECTION); // set the view volume shape
    glLoadIdentity();
    glOrtho(-2.0 * 64 / 48.0, 2.0 * 64 / 48.0, -2.0, 2.0, 0.1, 100);
    glMatrixMode(GL_MODELVIEW); // position and aim the camera
    glLoadIdentity();
    gluLookAt(2.0, 2.0, 2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3d(1, 0, 0); // draw black lines
    M->makeSurfaceMesh();
    M->draw();
    M->output();

    /*
    glColor3d(0, 0, 0); // draw black lines
    axis(0.5);                     // z-axis
    glPushMatrix();
    glRotated(90, 0, 1.0, 0);
    axis(0.5);                    // y-axis
    glRotated(-90.0, 1, 0, 0);
    axis(0.5);                    // z-axis
    glPopMatrix();

    glPushMatrix();
    glTranslated(0.5, 0.5, 0.5); // big cube at (0.5, 0.5, 0.5)
    glutWireCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslated(1.0, 1.0, 0);    // sphere at (1,1,0)
    glutWireSphere(0.25, 10, 8);
    glPopMatrix();

    glPushMatrix();
    glTranslated(1.0, 0, 1.0);    // cone at (1,0,1)
    glutWireCone(0.2, 0.5, 10, 8);
    glPopMatrix();

    glPushMatrix();
    glTranslated(1, 1, 1);
    glutWireTeapot(0.2); // teapot at (1,1,1)
    glPopMatrix();

    glPushMatrix();
    glTranslated(0, 1.0, 0); // torus at (0,1,0)
    glRotated(90.0, 1, 0, 0);
    glutWireTorus(0.1, 0.3, 10, 10);
    glPopMatrix();

    glPushMatrix();
    glTranslated(1.0, 0, 0); // dodecahedron at (1,0,0)
    glScaled(0.15, 0.15, 0.15);
    glutWireDodecahedron();
    glPopMatrix();

    glPushMatrix();
    glTranslated(0, 1.0, 1.0); // small cube at (0,1,1)
    glutWireCube(0.25);
    glPopMatrix();

    glPushMatrix();
    glTranslated(0, 0, 1.0); // cylinder at (0,0,1)
    GLUquadricObj * qobj;
    qobj = gluNewQuadric();
    gluQuadricDrawStyle(qobj, GLU_LINE);
    gluCylinder(qobj, 0.2, 0.2, 0.4, 8, 8);
    glPopMatrix();
    */

    glFlush();
}
void initLighting() {
    glEnable(GL_LIGHTING);
    // set up light colors (ambient, diffuse, specular)
    GLfloat lightKa[] = { 1.2f, 0.0f, 0.0f, 1.0f };  // ambient light
    GLfloat lightKd[] = { 1.7f, 0.0f, 0.0f, 1.0f };  // diffuse light
    GLfloat lightKs[] = { 1, 0, 0, 1 };           // specular light
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightKa);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightKd);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightKs);

    // position the light
    float lightPos[4] = { 0, 10, -20, 1 }; // positional light
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glEnable(GL_LIGHT0);                        // MUST enable each light source after configuration


}
//<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Transformation testbed - wireframes");
    glutDisplayFunc(displayWire);
    glEnable(GL_DEPTH_TEST);
    initLighting();
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);  // background is white
    glViewport(0, 0, 640, 480);
    glutMainLoop();
}

