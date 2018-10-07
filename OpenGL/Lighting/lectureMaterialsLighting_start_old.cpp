#if defined __APPLE__ && !defined X11
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<< displayWire >>>>>>>>>>>>>>>>>>>>>>
void displayObjects(void)
{
    glMatrixMode(GL_PROJECTION); // set the view volume shape
    glLoadIdentity();
    glOrtho(-2.0*64/48.0, 2.0*64/48.0, -2.0, 2.0, 0.1, 100);
    glMatrixMode(GL_MODELVIEW); // position and aim the camera
    glLoadIdentity();
    gluLookAt(2.0, 2.0, 2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
     glColor3d(1,0,0); // draw black lines
    glDisable(GL_LIGHT0);
    glPushMatrix();
    glTranslated(0, 1.5, -1); //lightPos
    glutSolidSphere(0.1, 10, 10);
    glPopMatrix();
    glEnable(GL_LIGHT0);
    GLfloat amb[] = {0.6f, 0.6f, 0.6, 0.5f};  // ambient
        GLfloat diff[] = {0.9f, 0.9f, 0.9, 0.5};  // diffuse
        GLfloat spec[] = {1,1, 1, 1};           // specular
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT, amb);
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE, diff);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS, 200.0);
    glPushMatrix();
    glTranslated(0,1,0);
    glutSolidSphere(0.25, 10, 8);
    glPopMatrix();
    GLfloat amb2[] = {1.0f, 0.0f, 0.0, 1.0f};  // ambient
        GLfloat diff2[] = {1.0f, 0.0f, 0.0, 1.0};  // diffuse
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT, amb2);
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE, diff2);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS, 7.0);
    glPushMatrix();
    glTranslated(-0.5,-0.2,0.2);
    glutSolidCone(0.2, 0.5, 10, 8);
    glPopMatrix();
    GLfloat amb3[] = {0.6f, 0.6f, 1.0, 0.3f};  // ambient
        GLfloat diff3[] = {0.9f, 0.9f, 1.0, 0.3};  // diffuse
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT, amb3);
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE, diff3);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS, 7.0);
    glPushMatrix();
    glTranslated(-2,1,1);
    glutSolidTeapot(0.2);
    glPopMatrix();
    GLfloat amb4[] = {0.6f, 1.0f, 0.6, 0.4f};  // ambient
        GLfloat diff4[] = {0.9f, 1.0f, 0.9, 0.4};  // diffuse
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT, amb4);
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE, diff4);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS, 7.0);
    glPushMatrix();
    glTranslated(1,1,1);
    glRotated(90.0, 1,0,0);
    glutSolidTorus(0.1, 0.3, 10,10);
    glPopMatrix();
    GLfloat amb5[] = {1.0f, 0.0f, 1.0, 0.5f};  // ambient
        GLfloat diff5[] = {1.0f, 0.0f, 1.0, 0.5};  // diffuse
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT, amb5);
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE, diff5);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS, 7.0);
    glPushMatrix();
    glTranslated(1,1.5,1);
    glTranslated(1.0, 0 ,0); // dodecahedron at (1,0,0)
    glScaled(0.15, 0.15, 0.15);
    glutSolidDodecahedron();
    glPopMatrix();
    glFlush();
    glutSwapBuffers();
}
void initMaterial(){
}
void initLighting(){
    glEnable(GL_LIGHTING);

    // set up light colors (ambient, diffuse, specular)

    GLfloat lightKa[] = {0.8f, 0.8f, 0.8f, 1.0f};       // ambient light
    // GLfloat lightKa[] = {1.0f, 0.0f, 0.0f, 1.0f};    // ambient light 1b: pure red
    // GLfloat lightKd[] = {0.8f, 0.8f, 0.8f, 1.0f};    // diffuse light
    GLfloat lightKd[] = {1.0f, 0.0f, 0.0f, 1.0f};       // diffuse light 1c 1e: pure red
    // GLfloat lightKs[] = {0.8f, 0.8f, 0.8f, 1};       // specular light
    GLfloat lightKs[] = {1.0f, 0.0f, 0.0f, 1};          // specular light 1d: pure red
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightKa);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightKd);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightKs);

    // position the light
    // float lightPos[4] = {1, -0.5, 2, 0};             // 1a
    float lightPos[4] = {0, 1.5, -1, 1};

    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glEnable(GL_LIGHT0);                                // MUST enable each light source after configuration
    // glDisable(GL_LIGHT0);

    // Add several lights
    // Light position
    // GLfloat light1Position[4] = {0.0, 0.0, 1.0, 0};  // back-front
    // GLfloat light1Position[4] = {0.0, 0.0, -1.0, 0}; // front-back
    // GLfloat light1Position[4] = {0.0, 1.0, 0.0, 0};  // top-down
    // GLfloat light1Position[4] = {0.0, -1.0, 0.0, 0}; // down-top
    // GLfloat light1Position[4] = {1.0, 0.0, 0.0, 0};  // right-left
    GLfloat light1Position[4] = {-1.0, 0.0, 0.0, 0}; // left-right
    // GLfloat light1Position[4] = {1.0, 1.0, 0.0, 0};  // upright-downleft
    // GLfloat light1Position[4] = {-1.0, -1.0, 0.0, 0};   // upright-downleft
    // GLfloat light1Position[4] = {1.0, -1.0, 0.0, 0};   // downright-upleft
    // GLfloat light1Position[4] = {-1.0, 1.0, 0.0, 0};   // upleft-downright

    // GLfloat light1Ka[] = {0.0f, 1.0f, 1.0f, 1};         // ambient light: pure red
    // GLfloat light1Kd[] = {0.0f, 1.0f, 1.0f, 1};         // diffuse light: pure red
    // GLfloat light1Ks[] = {0.0f, 1.0f, 1.0f, 1};         // specular light: pure red
    // GLfloat light1Ka[] = {1.0f, 0.0f, 0.0f, 1};         // ambient light: pure red
    // GLfloat light1Kd[] = {1.0f, 0.0f, 0.0f, 1};         // diffuse light: pure red
    // GLfloat light1Ks[] = {1.0f, 0.0f, 0.0f, 1};         // specular light: pure red
    // GLfloat light1Ka[] = {0.0f, 1.0f, 0.0f, 1};         // ambient light: pure green
    // GLfloat light1Kd[] = {0.0f, 1.0f, 0.0f, 1};         // diffuse light: pure green
    // GLfloat light1Ks[] = {0.0f, 1.0f, 0.0f, 1};         // specular light: pure green
    GLfloat light1Ka[] = {0.0f, 0.0f, 1.0f, 1.0};         // ambient light: pure blue
    GLfloat light1Kd[] = {0.0f, 0.0f, 1.0f, 1.0};         // diffuse light: pure blue
    GLfloat light1Ks[] = {0.0f, 0.0f, 1.0f, 1.0};         // specular light: pure blue
    glLightfv(GL_LIGHT1, GL_POSITION, light1Position);
    glLightfv(GL_LIGHT1, GL_AMBIENT, light1Ka);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1Kd);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light1Ks);
    glEnable(GL_LIGHT1);
    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHT1);

    GLfloat light3Ka[] = {1.0f, 1.0f, 1.0f, 1.0};         // ambient light: pure white
    GLfloat light3Kd[] = {1.0f, 1.0f, 1.0f, 1.0};         // diffuse light: pure white
    GLfloat light3Ks[] = {1.0f, 1.0f, 1.0f, 1.0};         // specular light: pure white
    GLfloat light3Position[4] = {-2.0, 1.0, 0.0, 1}; // left-right
    // GLfloat light3Position[4] = {-2.0, 1.0, -1.0, 1}; // left-right
    // GLfloat light3Position[4] = {-2.0, 1.0, -2.0, 1}; // left-right
    // GLfloat light3Position[4] = {-2.0, 1.0, -3.0, 1}; // left-right
    // GLfloat light3Direction[4] = {0, 0, 0, 1};
    // double pi = 4 * atan(1);
    GLfloat light3Direction[4] = {-0.03, 0.06, -1.0, 1};
    glLightfv(GL_LIGHT3, GL_POSITION, light3Position);
    glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, light3Direction);
    glLightfv(GL_LIGHT3, GL_AMBIENT, light3Ka);
    glLightfv(GL_LIGHT3, GL_DIFFUSE, light3Kd);
    glLightfv(GL_LIGHT3, GL_SPECULAR, light3Ks);
    // glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 45.0);
    glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 3.0);
	glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, 20.0);
    glLightf(GL_LIGHT3, GL_CONSTANT_ATTENUATION, 2.0);
    glEnable(GL_LIGHT3);
}

//<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB );
    glutInitWindowSize(640,480);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Materials and Lighting testbed");
    glutDisplayFunc(displayObjects);
    glEnable(GL_DEPTH_TEST);
    initLighting();
    initMaterial();
    glClearColor(1.0f, 1.0f, 1.0f,0.0f);  // background is white
    //glEnable(GL_FLAT);
        glShadeModel(GL_SMOOTH);
    glEnable(GL_SMOOTH);
    glViewport(0, 0, 640, 480);
    glutMainLoop();
}

