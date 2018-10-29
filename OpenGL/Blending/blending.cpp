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
#include <cmath>
#include <cstdio>
#include <cstring>
// #include <FreeImage.h>
#include <fstream>
#include <iostream>

GLenum SourceF, DestinationF;

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<< displayObjects >>>>>>>>>>>>>>>>>>>>>>

void displayObjects(void)

{
  glMatrixMode(GL_PROJECTION); // set the view volume shape
  glLoadIdentity();
  glOrtho(-2.0 * 64 / 48.0, 2.0 * 64 / 48.0, -2.0, 2.0, 0.1, 100);
  glMatrixMode(GL_MODELVIEW); // position and aim the camera
  glLoadIdentity();
  gluLookAt(2.0, 2.0, 2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glColor3d(1, 0, 0); // draw black lines

  // glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, 3.0);
  // glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
  // glEnable(GL_COLOR_MATERIAL);

  glEnable(GL_BLEND);
  // glDisable(GL_BLEND);

  // glEnable(GL_TEXTURE_2D);
  // glEnable(GL_COLOR_LOGIC_OP);

  // glLogicOp (GL_OR);

  // order: sphere, cone, teapot, torus, Dodecahedron

  GLfloat amb[] = {0.6f, 0.6f, 0.6, 0.5f}; // ambient
  GLfloat diff[] = {0.9f, 0.9f, 0.9, 0.5}; // diffuse
  GLfloat spec[] = {1, 1, 1, 1};           // specular
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amb);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 7.0);

  glPushMatrix();
  glTranslated(0, 1, 0);
  glutSolidSphere(0.25, 10, 8);
  glPopMatrix();

  GLfloat amb2[] = {1.0f, 0.0f, 0.0, 1.0f}; // ambient
  GLfloat diff2[] = {1.0f, 0.0f, 0.0, 1.0}; // diffuse
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amb2);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff2);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 7.0);

  glPushMatrix();
  glTranslated(0.2, 0.2, 0.2);
  glutSolidCone(0.2, 0.5, 10, 8);
  glPopMatrix();

  GLfloat amb3[] = {0.6f, 0.6f, 1.0, 0.3f}; // ambient
  GLfloat diff3[] = {0.9f, 0.9f, 1.0, 0.3}; // diffuse
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amb3);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff3);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 7.0);

  glPushMatrix();
  glTranslated(1, 1, 1);
  glutSolidTeapot(0.2);
  glPopMatrix();

  GLfloat amb4[] = {0.6f, 1.0f, 0.6, 0.4f}; // ambient
  GLfloat diff4[] = {0.9f, 1.0f, 0.9, 0.4}; // diffuse
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amb4);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff4);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 7.0);

  glPushMatrix();
  glTranslated(1, 1, 1);
  glRotated(90.0, 1, 0, 0);
  glutSolidTorus(0.1, 0.3, 10, 10);
  glPopMatrix();

  GLfloat amb5[] = {1.0f, 0.0f, 1.0, 0.5f}; // ambient
  GLfloat diff5[] = {1.0f, 0.0f, 1.0, 0.5}; // diffuse
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amb5);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff5);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 7.0);

  glPushMatrix();
  glTranslated(1, 1.5, 1);
  glScaled(0.15, 0.15, 0.15);
  glutSolidDodecahedron();
  glPopMatrix();

  glFlush();
  glutSwapBuffers();
}

void initMaterial() {}

void initLighting() {

  glEnable(GL_LIGHTING);

  // set up light colors (ambient, diffuse, specular)

  GLfloat lightKa[] = {0.8f, 0.8f, 0.8f, 1.0f}; // ambient light
  GLfloat lightKd[] = {0.8f, 0.8f, 0.8f, 1.0f}; // diffuse light
  GLfloat lightKs[] = {0.8f, 0.8f, 0.8f, 1};    // specular light

  glLightfv(GL_LIGHT0, GL_AMBIENT, lightKa);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, lightKd);
  glLightfv(GL_LIGHT0, GL_SPECULAR, lightKs);

  // position the light
  float lightPos[4] = {0, 20, -10, 1}; // positional light
  glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
  glEnable(GL_LIGHT0); // MUST enable each light source after configuration
}

void myKey(unsigned char key, int x, int y) {

  switch (key) {
  case '0':
    SourceF = GL_ZERO;
    break;
  case '1':
    SourceF = GL_ONE;
    break;
  case '2':
    SourceF = GL_SRC_COLOR;
    break;
  case '3':
    SourceF = GL_ONE_MINUS_SRC_COLOR;
    break;
  case '4':
    SourceF = GL_SRC_ALPHA;
    break;
  case '5':
    SourceF = GL_ONE_MINUS_SRC_ALPHA;
    break;
  case '6':
    SourceF = GL_DST_ALPHA;
    break;
  case '7':
    SourceF = GL_ONE_MINUS_DST_ALPHA;
    break;
  case '8':
    SourceF = GL_ONE_MINUS_DST_COLOR;
    break;
  //---------------------------
  case 'q':
    DestinationF = GL_ZERO;
    break;
  case 'w':
    DestinationF = GL_ONE;
    break;
  case 'e':
    DestinationF = GL_DST_COLOR;
    break;
  case 'r':
    DestinationF = GL_ONE_MINUS_DST_COLOR;
    break;
  case 't':
    DestinationF = GL_SRC_ALPHA;
    break;
  case 'y':
    DestinationF = GL_ONE_MINUS_SRC_ALPHA;
    break;
  case 'u':
    DestinationF = GL_DST_ALPHA;
    break;
  case 'i':
    DestinationF = GL_ONE_MINUS_DST_ALPHA;
    break;
  case 'o':
    DestinationF = GL_ONE_MINUS_DST_COLOR;
    break;
  case 'd':
    glEnable(GL_DEPTH_TEST);
    break;
  case 'D':
    glDisable(GL_DEPTH_TEST);
    break;
  default:
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    break;
  }

  glBlendFunc(SourceF, DestinationF);
  glutPostRedisplay();
}
//<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

int main(int argc, char **argv)

{
  SourceF = GL_ONE;
  DestinationF = GL_ZERO;
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(640, 480);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("Blending testbed");
  glutDisplayFunc(displayObjects);
  glutKeyboardFunc(myKey);
  glEnable(GL_DEPTH_TEST);
  initLighting();
  initMaterial();
  glClearColor(1.0f, 1.0f, 1.0f, 0.0f); // background is white
  glShadeModel(GL_SMOOTH);
  glEnable(GL_SMOOTH);
  glViewport(0, 0, 640, 480);
  glutMainLoop();
}
