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
#include <FreeImage.h>
#include <iostream>
// #ifndef OPTION
// #define OPTION "0"
// #endif

#define WIDTH 640
#define HEIGHT 480
#define BitsPerPixel 24

using namespace std;

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
    sprintf(filename, "%s.png", OPTION);
    printf("%s\n", filename);
    if (FreeImage_Save(FIF_PNG, bitmap, filename, 0))
        cout << "Image succesfully saved!\n";
    FreeImage_DeInitialise();
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<< displayWire >>>>>>>>>>>>>>>>>>>>>>

void displayObjects(void) {
    glMatrixMode(GL_PROJECTION); // set the view volume shape
    glLoadIdentity();
    glOrtho(-2.0*64/48.0, 2.0*64/48.0, -2.0, 2.0, 0.1, 100);

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

    if (strcmp(OPTION, "4") == 0) {
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
    }
    else if (   strcmp(OPTION, "4aa1") == 0
            || strcmp(OPTION, "4b1a1") == 0
            || strcmp(OPTION, "4b2a1") == 0
            || strcmp(OPTION, "4b3a1") == 0) {
        GLfloat amb1[] = {0.1f, 0.2f, 0.3f, 0.5f};  // ambient
        GLfloat amb2[] = {0.9f, 0.6f, 0.3f, 1.0f};  // ambient
        GLfloat amb3[] = {0.3f, 0.3f, 0.9f, 0.3f};  // ambient
        GLfloat amb4[] = {0.6f, 0.2f, 0.6f, 0.4f};  // ambient
        GLfloat amb5[] = {0.9f, 0.3f, 0.9f, 0.5f};  // ambient
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
    }
    else if (   strcmp(OPTION, "4aa2") == 0
            || strcmp(OPTION, "4b1a2") == 0
            || strcmp(OPTION, "4b2a2") == 0
            || strcmp(OPTION, "4b3a2") == 0) {
        GLfloat amb1[] = {0.2f, 0.4f, 0.6f, 0.5f};  // ambient
        GLfloat amb2[] = {0.6f, 0.4f, 0.2f, 1.0f};  // ambient
        GLfloat amb3[] = {0.5f, 0.5f, 1.0f, 0.3f};  // ambient
        GLfloat amb4[] = {0.8f, 0.4f, 0.8f, 0.4f};  // ambient
        GLfloat amb5[] = {0.9f, 0.3f, 0.9f, 0.5f};  // ambient
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
    }
    else if (   strcmp(OPTION, "4aa3") == 0
            || strcmp(OPTION, "4b1a3") == 0
            || strcmp(OPTION, "4b2a3") == 0
            || strcmp(OPTION, "4b3a3") == 0) {
        GLfloat amb1[] = {0.3f, 0.6f, 0.9f, 0.5f};  // ambient
        GLfloat amb2[] = {0.9f, 0.6f, 0.3f, 1.0f};  // ambient
        GLfloat amb3[] = {1.0f, 0.5f, 1.0f, 0.3f};  // ambient
        GLfloat amb4[] = {0.9f, 0.6f, 0.9f, 0.4f};  // ambient
        GLfloat amb5[] = {0.8f, 0.8f, 0.4f, 0.5f};  // ambient
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
    }
    else if (   strcmp(OPTION, "4ad1") == 0
            || strcmp(OPTION, "4b1d1") == 0
            || strcmp(OPTION, "4b2d1") == 0
            || strcmp(OPTION, "4b3d1") == 0) {
        GLfloat amb1[] = {0.6f, 0.6f, 0.6f, 0.5f};  // ambient
        GLfloat amb2[] = {1.0f, 0.0f, 0.0f, 1.0f};  // ambient
        GLfloat amb3[] = {0.6f, 0.6f, 1.0f, 0.3f};  // ambient
        GLfloat amb4[] = {0.6f, 1.0f, 0.6f, 0.4f};  // ambient
        GLfloat amb5[] = {1.0f, 0.0f, 1.0f, 0.5f};  // ambient
        GLfloat dif1[] = {0.6f, 0.7f, 0.8f, 0.5f};  // diffuse
        GLfloat dif2[] = {1.0f, 0.2f, 0.4f, 1.0f};  // diffuse
        GLfloat dif3[] = {0.5f, 0.5f, 1.0f, 0.3f};  // diffuse
        GLfloat dif4[] = {0.3f, 0.6f, 0.9f, 0.4f};  // diffuse
        GLfloat dif5[] = {0.9f, 0.3f, 0.9f, 0.5f};  // diffuse
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
    }
    else if (   strcmp(OPTION, "4ad2") == 0
            || strcmp(OPTION, "4b1d2") == 0
            || strcmp(OPTION, "4b2d2") == 0
            || strcmp(OPTION, "4b3d2") == 0) {
        GLfloat amb1[] = {0.6f, 0.6f, 0.6f, 0.5f};  // ambient
        GLfloat amb2[] = {1.0f, 0.0f, 0.0f, 1.0f};  // ambient
        GLfloat amb3[] = {0.6f, 0.6f, 1.0f, 0.3f};  // ambient
        GLfloat amb4[] = {0.6f, 1.0f, 0.6f, 0.4f};  // ambient
        GLfloat amb5[] = {1.0f, 0.0f, 1.0f, 0.5f};  // ambient
        GLfloat dif1[] = {0.6f, 0.8f, 1.0f, 0.5f};  // diffuse
        GLfloat dif2[] = {1.0f, 0.3f, 0.6f, 1.0f};  // diffuse
        GLfloat dif3[] = {0.7f, 0.7f, 1.0f, 0.3f};  // diffuse
        GLfloat dif4[] = {0.4f, 0.7f, 1.0f, 0.4f};  // diffuse
        GLfloat dif5[] = {0.8f, 0.4f, 0.8f, 0.5f};  // diffuse
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
    }
    else if (   strcmp(OPTION, "4ad3") == 0
            || strcmp(OPTION, "4b1d3") == 0
            || strcmp(OPTION, "4b2d3") == 0
            || strcmp(OPTION, "4b3d3") == 0) {
        GLfloat amb1[] = {0.6f, 0.6f, 0.6f, 0.5f};  // ambient
        GLfloat amb2[] = {1.0f, 0.0f, 0.0f, 1.0f};  // ambient
        GLfloat amb3[] = {0.6f, 0.6f, 1.0f, 0.3f};  // ambient
        GLfloat amb4[] = {0.6f, 1.0f, 0.6f, 0.4f};  // ambient
        GLfloat amb5[] = {1.0f, 0.0f, 1.0f, 0.5f};  // ambient
        GLfloat dif1[] = {0.2f, 0.6f, 1.0f, 0.5f};  // diffuse
        GLfloat dif2[] = {1.0f, 0.5f, 1.0f, 1.0f};  // diffuse
        GLfloat dif3[] = {0.7f, 0.7f, 0.4f, 0.3f};  // diffuse
        GLfloat dif4[] = {0.3f, 0.8f, 0.9f, 0.4f};  // diffuse
        GLfloat dif5[] = {0.7f, 0.3f, 0.9f, 0.5f};  // diffuse
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
    }
    else if (   strcmp(OPTION, "4as1") == 0
            || strcmp(OPTION, "4b1s1") == 0
            || strcmp(OPTION, "4b2s1") == 0
            || strcmp(OPTION, "4b3s1") == 0) {
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
        GLfloat spe1[] = {1.0f, 1.0f, 0.0f, 1.0f};  // specular
        GLfloat spe2[] = {1.0f, 1.0f, 0.0f, 1.0f};  // specular
        GLfloat spe3[] = {1.0f, 1.0f, 0.0f, 1.0f};  // specular
        GLfloat spe4[] = {1.0f, 1.0f, 0.0f, 1.0f};  // specular
        GLfloat spe5[] = {1.0f, 1.0f, 0.0f, 1.0f};  // specular
        GLfloat shini1 = 200.0f;                    // shininess sphere
        GLfloat shini2 = 7.0f;                      // shininess cone
        GLfloat shini3 = 7.0f;                      // shininess teapot
        GLfloat shini4 = 7.0f;                      // shininess torus
        GLfloat shini5 = 7.0f;                      // shininess dodecahedron
        draw(amb1, amb2, amb3, amb4, amb5, dif1, dif2, dif3, dif4, dif5, spe1,
                spe2, spe3, spe4, spe5, shini1, shini2, shini3, shini4, shini5);
    }
    else if (   strcmp(OPTION, "4as2") == 0
            || strcmp(OPTION, "4b1s2") == 0
            || strcmp(OPTION, "4b2s2") == 0
            || strcmp(OPTION, "4b3s2") == 0) {
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
        GLfloat spe1[] = {1.0f, 0.0f, 1.0f, 1.0f};  // specular
        GLfloat spe2[] = {1.0f, 0.0f, 1.0f, 1.0f};  // specular
        GLfloat spe3[] = {1.0f, 0.0f, 1.0f, 1.0f};  // specular
        GLfloat spe4[] = {1.0f, 0.0f, 1.0f, 1.0f};  // specular
        GLfloat spe5[] = {1.0f, 0.0f, 1.0f, 1.0f};  // specular
        GLfloat shini1 = 200.0f;                    // shininess sphere
        GLfloat shini2 = 7.0f;                      // shininess cone
        GLfloat shini3 = 7.0f;                      // shininess teapot
        GLfloat shini4 = 7.0f;                      // shininess torus
        GLfloat shini5 = 7.0f;                      // shininess dodecahedron
        draw(amb1, amb2, amb3, amb4, amb5, dif1, dif2, dif3, dif4, dif5, spe1,
                spe2, spe3, spe4, spe5, shini1, shini2, shini3, shini4, shini5);
    }
    else if (   strcmp(OPTION, "4as3") == 0
            || strcmp(OPTION, "4b1s3") == 0
            || strcmp(OPTION, "4b2s3") == 0
            || strcmp(OPTION, "4b3s3") == 0) {
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
        GLfloat spe1[] = {0.0f, 1.0f, 1.0f, 1.0f};  // specular
        GLfloat spe2[] = {0.0f, 1.0f, 1.0f, 1.0f};  // specular
        GLfloat spe3[] = {0.0f, 1.0f, 1.0f, 1.0f};  // specular
        GLfloat spe4[] = {0.0f, 1.0f, 1.0f, 1.0f};  // specular
        GLfloat spe5[] = {0.0f, 1.0f, 1.0f, 1.0f};  // specular
        GLfloat shini1 = 200.0f;                    // shininess sphere
        GLfloat shini2 = 7.0f;                      // shininess cone
        GLfloat shini3 = 7.0f;                      // shininess teapot
        GLfloat shini4 = 7.0f;                      // shininess torus
        GLfloat shini5 = 7.0f;                      // shininess dodecahedron
        draw(amb1, amb2, amb3, amb4, amb5, dif1, dif2, dif3, dif4, dif5, spe1,
                spe2, spe3, spe4, spe5, shini1, shini2, shini3, shini4, shini5);
    }
    else if (   strcmp(OPTION, "4ash1") == 0
            || strcmp(OPTION, "4b1sh1") == 0
            || strcmp(OPTION, "4b2sh1") == 0
            || strcmp(OPTION, "4b3sh1") == 0) {
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
        GLfloat shini1 = 5.0f;                      // shininess sphere
        GLfloat shini2 = 5.0f;                      // shininess cone
        GLfloat shini3 = 5.0f;                      // shininess teapot
        GLfloat shini4 = 5.0f;                      // shininess torus
        GLfloat shini5 = 5.0f;                      // shininess dodecahedron
        draw(amb1, amb2, amb3, amb4, amb5, dif1, dif2, dif3, dif4, dif5, spe1,
                spe2, spe3, spe4, spe5, shini1, shini2, shini3, shini4, shini5);
    }
    else if (   strcmp(OPTION, "4ash2") == 0
            || strcmp(OPTION, "4b1sh2") == 0
            || strcmp(OPTION, "4b2sh2") == 0
            || strcmp(OPTION, "4b3sh2") == 0) {
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
        GLfloat shini1 = 50.0f;                     // shininess sphere
        GLfloat shini2 = 50.0f;                     // shininess cone
        GLfloat shini3 = 50.0f;                     // shininess teapot
        GLfloat shini4 = 50.0f;                     // shininess torus
        GLfloat shini5 = 50.0f;                     // shininess dodecahedron
        draw(amb1, amb2, amb3, amb4, amb5, dif1, dif2, dif3, dif4, dif5, spe1,
                spe2, spe3, spe4, spe5, shini1, shini2, shini3, shini4, shini5);
    }
    else if (   strcmp(OPTION, "4ash3") == 0
            || strcmp(OPTION, "4b1sh3") == 0
            || strcmp(OPTION, "4b2sh3") == 0
            || strcmp(OPTION, "4b3sh3") == 0) {
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
        GLfloat shini1 = 100.0f;                    // shininess sphere
        GLfloat shini2 = 100.0f;                    // shininess cone
        GLfloat shini3 = 100.0f;                    // shininess teapot
        GLfloat shini4 = 100.0f;                    // shininess torus
        GLfloat shini5 = 100.0f;                    // shininess dodecahedron
        draw(amb1, amb2, amb3, amb4, amb5, dif1, dif2, dif3, dif4, dif5, spe1,
                spe2, spe3, spe4, spe5, shini1, shini2, shini3, shini4, shini5);
    }
    else if (   strcmp(OPTION, "4ash4") == 0
            || strcmp(OPTION, "4b1sh4") == 0
            || strcmp(OPTION, "4b2sh4") == 0
            || strcmp(OPTION, "4b3sh4") == 0) {
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
        GLfloat shini1 = 150.0f;                    // shininess sphere
        GLfloat shini2 = 150.0f;                    // shininess cone
        GLfloat shini3 = 150.0f;                    // shininess teapot
        GLfloat shini4 = 150.0f;                    // shininess torus
        GLfloat shini5 = 150.0f;                    // shininess dodecahedron
        draw(amb1, amb2, amb3, amb4, amb5, dif1, dif2, dif3, dif4, dif5, spe1,
                spe2, spe3, spe4, spe5, shini1, shini2, shini3, shini4, shini5);
    }
    else {
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
    }

    saveImage();
    glFlush();
    glutSwapBuffers();
}

void initMaterial() {

}

void initLighting() {
    if (strcmp(OPTION, "0") == 0) {
        printf("OPTION: %s\n", OPTION);
        glEnable(GL_LIGHTING);
        // set up light colors (ambient, diffuse, specular)
        GLfloat light0Ka[] = {0.8f, 0.8f, 0.8f, 1.0f};   // ambient light
        GLfloat light0Kd[] = {0.8f, 0.8f, 0.8f, 1.0f};   // diffuse light
        GLfloat light0Ks[] = {0.8f, 0.8f, 0.8f, 1.0f};   // specular light
        glLightfv(GL_LIGHT0, GL_AMBIENT, light0Ka);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, light0Kd);
        glLightfv(GL_LIGHT0, GL_SPECULAR, light0Ks);
        // position the light
        float lightPos[4] = {0, 1.5, -1, 1};
        glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
        glEnable(GL_LIGHT0);  // MUST enable each light source after configuration
    }
    else if (strcmp(OPTION, "1a") == 0) {
        printf("OPTION: %s\n", OPTION);
        glEnable(GL_LIGHTING);
        // set up light colors (ambient, diffuse, specular)
        GLfloat light0Ka[] = {0.8f, 0.8f, 0.8f, 1.0f};   // ambient light
        GLfloat light0Kd[] = {0.8f, 0.8f, 0.8f, 1.0f};   // diffuse light
        GLfloat light0Ks[] = {0.8f, 0.8f, 0.8f, 1.0f};   // specular light
        glLightfv(GL_LIGHT0, GL_AMBIENT, light0Ka);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, light0Kd);
        glLightfv(GL_LIGHT0, GL_SPECULAR, light0Ks);
        // position the light
        float lightPos[4] = {1, -0.5, 2, 0};
        glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
        glEnable(GL_LIGHT0);  // MUST enable each light source after configuration
    }
    else if (strcmp(OPTION, "1b") == 0) {
        printf("OPTION: %s\n", OPTION);
        glEnable(GL_LIGHTING);
        // set up light colors (ambient, diffuse, specular)
        GLfloat light0Ka[] = {1.0f, 0.0f, 0.0f, 1.0f};   // ambient light
        GLfloat light0Kd[] = {0.8f, 0.8f, 0.8f, 1.0f};   // diffuse light
        GLfloat light0Ks[] = {0.8f, 0.8f, 0.8f, 1.0f};   // specular light
        glLightfv(GL_LIGHT0, GL_AMBIENT, light0Ka);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, light0Kd);
        glLightfv(GL_LIGHT0, GL_SPECULAR, light0Ks);
        // position the light
        float lightPos[4] = {0, 1.5, -1, 1};
        glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
        glEnable(GL_LIGHT0);  // MUST enable each light source after configuration
    }
    else if (strcmp(OPTION, "1c") == 0) {
        printf("OPTION: %s\n", OPTION);
        glEnable(GL_LIGHTING);
        // set up light colors (ambient, diffuse, specular)
        GLfloat light0Ka[] = {0.8f, 0.8f, 0.8f, 1.0f};   // ambient light
        GLfloat light0Kd[] = {1.0f, 0.0f, 0.0f, 1.0f};   // diffuse light
        GLfloat light0Ks[] = {0.8f, 0.8f, 0.8f, 1.0f};   // specular light
        glLightfv(GL_LIGHT0, GL_AMBIENT, light0Ka);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, light0Kd);
        glLightfv(GL_LIGHT0, GL_SPECULAR, light0Ks);
        // position the light
        float lightPos[4] = {0, 1.5, -1, 1};
        glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
        glEnable(GL_LIGHT0);  // MUST enable each light source after configuration
    }
    else if (strcmp(OPTION, "1d") == 0) {
        printf("OPTION: %s\n", OPTION);
        glEnable(GL_LIGHTING);
        // set up light colors (ambient, diffuse, specular)
        GLfloat light0Ka[] = {0.8f, 0.8f, 0.8f, 1.0f};   // ambient light
        GLfloat light0Kd[] = {0.8f, 0.8f, 0.8f, 1.0f};   // diffuse light
        GLfloat light0Ks[] = {1.0f, 0.0f, 0.0f, 1.0f};   // specular light
        glLightfv(GL_LIGHT0, GL_AMBIENT, light0Ka);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, light0Kd);
        glLightfv(GL_LIGHT0, GL_SPECULAR, light0Ks);
        // position the light
        float lightPos[4] = {0, 1.5, -1, 1};
        glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
        glEnable(GL_LIGHT0);  // MUST enable each light source after configuration
    }
    else if (strcmp(OPTION, "1e") == 0) {
        printf("OPTION: %s\n", OPTION);
        glEnable(GL_LIGHTING);
        // set up light colors (ambient, diffuse, specular)
        GLfloat light0Ka[] = {0.8f, 0.8f, 0.8f, 1.0f};   // ambient light
        GLfloat light0Kd[] = {1.0f, 0.0f, 0.0f, 1.0f};   // diffuse light
        GLfloat light0Ks[] = {1.0f, 0.0f, 0.0f, 1.0f};   // specular light
        glLightfv(GL_LIGHT0, GL_AMBIENT, light0Ka);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, light0Kd);
        glLightfv(GL_LIGHT0, GL_SPECULAR, light0Ks);
        // position the light
        float lightPos[4] = {0, 1.5, -1, 1};
        glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
        glEnable(GL_LIGHT0);  // MUST enable each light source after configuration
    }
    else if (strcmp(OPTION, "2.lr") == 0) {
        printf("OPTION: %s\n", OPTION);
        glEnable(GL_LIGHTING);
        // set up light colors (ambient, diffuse, specular)
        GLfloat light0Ka[] = {0.8f, 0.8f, 0.8f, 1.0f};   // ambient light
        GLfloat light0Kd[] = {0.8f, 0.8f, 0.8f, 1.0f};   // diffuse light
        GLfloat light0Ks[] = {0.8f, 0.8f, 0.8f, 1.0f};   // specular light
        glLightfv(GL_LIGHT0, GL_AMBIENT, light0Ka);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, light0Kd);
        glLightfv(GL_LIGHT0, GL_SPECULAR, light0Ks);
        // position the light
        float lightPos[4] = {0, 1.5, -1, 1};
        glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
        glEnable(GL_LIGHT0);  // MUST enable each light source after configuration

        GLfloat light1Ka[] = {0.3f, 0.0f, 0.9f, 1.0f};   // ambient light
        GLfloat light1Kd[] = {0.3f, 0.0f, 0.9f, 1.0f};   // diffuse light
        GLfloat light1Ks[] = {0.3f, 0.0f, 0.9f, 1.0f};   // specular light
        glLightfv(GL_LIGHT1, GL_AMBIENT, light1Ka);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, light1Kd);
        glLightfv(GL_LIGHT1, GL_SPECULAR, light1Ks);
        // position the light
        float light1Pos[4] = {-1.0f, 0.0f, 0.0f, 0};
        glLightfv(GL_LIGHT1, GL_POSITION, light1Pos);
        glEnable(GL_LIGHT1);  // MUST enable each light source after configuration
    }
    else if (strcmp(OPTION, "2.rl") == 0) {
        printf("OPTION: %s\n", OPTION);
        glEnable(GL_LIGHTING);
        // set up light colors (ambient, diffuse, specular)
        GLfloat light0Ka[] = {0.8f, 0.8f, 0.8f, 1.0f};   // ambient light
        GLfloat light0Kd[] = {0.8f, 0.8f, 0.8f, 1.0f};   // diffuse light
        GLfloat light0Ks[] = {0.8f, 0.8f, 0.8f, 1.0f};   // specular light
        glLightfv(GL_LIGHT0, GL_AMBIENT, light0Ka);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, light0Kd);
        glLightfv(GL_LIGHT0, GL_SPECULAR, light0Ks);
        // position the light
        float lightPos[4] = {0, 1.5, -1, 1};
        glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
        glEnable(GL_LIGHT0);  // MUST enable each light source after configuration

        GLfloat light1Ka[] = {0.3f, 0.0f, 0.9f, 1.0f};   // ambient light
        GLfloat light1Kd[] = {0.3f, 0.0f, 0.9f, 1.0f};   // diffuse light
        GLfloat light1Ks[] = {0.3f, 0.0f, 0.9f, 1.0f};   // specular light
        glLightfv(GL_LIGHT1, GL_AMBIENT, light1Ka);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, light1Kd);
        glLightfv(GL_LIGHT1, GL_SPECULAR, light1Ks);
        // position the light
        float light1Pos[4] = {1.0f, 0.0f, 0.0f, 0};
        glLightfv(GL_LIGHT1, GL_POSITION, light1Pos);
        glEnable(GL_LIGHT1);  // MUST enable each light source after configuration
    }
    else if (strcmp(OPTION, "2.tb") == 0) {
        printf("OPTION: %s\n", OPTION);
        glEnable(GL_LIGHTING);
        // set up light colors (ambient, diffuse, specular)
        GLfloat light0Ka[] = {0.8f, 0.8f, 0.8f, 1.0f};   // ambient light
        GLfloat light0Kd[] = {0.8f, 0.8f, 0.8f, 1.0f};   // diffuse light
        GLfloat light0Ks[] = {0.8f, 0.8f, 0.8f, 1.0f};   // specular light
        glLightfv(GL_LIGHT0, GL_AMBIENT, light0Ka);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, light0Kd);
        glLightfv(GL_LIGHT0, GL_SPECULAR, light0Ks);
        // position the light
        float lightPos[4] = {0, 1.5, -1, 1};
        glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
        glEnable(GL_LIGHT0);  // MUST enable each light source after configuration

        GLfloat light1Ka[] = {0.3f, 0.0f, 0.9f, 1.0f};   // ambient light
        GLfloat light1Kd[] = {0.3f, 0.0f, 0.9f, 1.0f};   // diffuse light
        GLfloat light1Ks[] = {0.3f, 0.0f, 0.9f, 1.0f};   // specular light
        glLightfv(GL_LIGHT1, GL_AMBIENT, light1Ka);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, light1Kd);
        glLightfv(GL_LIGHT1, GL_SPECULAR, light1Ks);
        // position the light
        float light1Pos[4] = {0.0f, 1.0f, 0.0f, 0};
        glLightfv(GL_LIGHT1, GL_POSITION, light1Pos);
        glEnable(GL_LIGHT1);  // MUST enable each light source after configuration
    }
    else if (strcmp(OPTION, "2.bt") == 0) {
        printf("OPTION: %s\n", OPTION);
        glEnable(GL_LIGHTING);
        // set up light colors (ambient, diffuse, specular)
        GLfloat light0Ka[] = {0.8f, 0.8f, 0.8f, 1.0f};   // ambient light
        GLfloat light0Kd[] = {0.8f, 0.8f, 0.8f, 1.0f};   // diffuse light
        GLfloat light0Ks[] = {0.8f, 0.8f, 0.8f, 1.0f};   // specular light
        glLightfv(GL_LIGHT0, GL_AMBIENT, light0Ka);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, light0Kd);
        glLightfv(GL_LIGHT0, GL_SPECULAR, light0Ks);
        // position the light
        float lightPos[4] = {0, 1.5, -1, 1};
        glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
        glEnable(GL_LIGHT0);  // MUST enable each light source after configuration

        GLfloat light1Ka[] = {0.3f, 0.0f, 0.9f, 1.0f};   // ambient light
        GLfloat light1Kd[] = {0.3f, 0.0f, 0.9f, 1.0f};   // diffuse light
        GLfloat light1Ks[] = {0.3f, 0.0f, 0.9f, 1.0f};   // specular light
        glLightfv(GL_LIGHT1, GL_AMBIENT, light1Ka);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, light1Kd);
        glLightfv(GL_LIGHT1, GL_SPECULAR, light1Ks);
        // position the light
        float light1Pos[4] = {0.0f, -1.0f, 0.0f, 0};
        glLightfv(GL_LIGHT1, GL_POSITION, light1Pos);
        glEnable(GL_LIGHT1);  // MUST enable each light source after configuration
    }
    else if (strcmp(OPTION, "2.bf") == 0) {
        printf("OPTION: %s\n", OPTION);
        glEnable(GL_LIGHTING);
        // set up light colors (ambient, diffuse, specular)
        GLfloat light0Ka[] = {0.8f, 0.8f, 0.8f, 1.0f};   // ambient light
        GLfloat light0Kd[] = {0.8f, 0.8f, 0.8f, 1.0f};   // diffuse light
        GLfloat light0Ks[] = {0.8f, 0.8f, 0.8f, 1.0f};   // specular light
        glLightfv(GL_LIGHT0, GL_AMBIENT, light0Ka);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, light0Kd);
        glLightfv(GL_LIGHT0, GL_SPECULAR, light0Ks);
        // position the light
        float lightPos[4] = {0, 1.5, -1, 1};
        glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
        glEnable(GL_LIGHT0);  // MUST enable each light source after configuration

        GLfloat light1Ka[] = {0.3f, 0.0f, 0.9f, 1.0f};   // ambient light
        GLfloat light1Kd[] = {0.3f, 0.0f, 0.9f, 1.0f};   // diffuse light
        GLfloat light1Ks[] = {0.3f, 0.0f, 0.9f, 1.0f};   // specular light
        glLightfv(GL_LIGHT1, GL_AMBIENT, light1Ka);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, light1Kd);
        glLightfv(GL_LIGHT1, GL_SPECULAR, light1Ks);
        // position the light
        float light1Pos[4] = {0.0f, 0.0f, 1.0f, 0};
        glLightfv(GL_LIGHT1, GL_POSITION, light1Pos);
        glEnable(GL_LIGHT1);  // MUST enable each light source after configuration
    }
    else if (strcmp(OPTION, "2.fb") == 0) {
        printf("OPTION: %s\n", OPTION);
        glEnable(GL_LIGHTING);
        // set up light colors (ambient, diffuse, specular)
        GLfloat light0Ka[] = {0.8f, 0.8f, 0.8f, 1.0f};   // ambient light
        GLfloat light0Kd[] = {0.8f, 0.8f, 0.8f, 1.0f};   // diffuse light
        GLfloat light0Ks[] = {0.8f, 0.8f, 0.8f, 1.0f};   // specular light
        glLightfv(GL_LIGHT0, GL_AMBIENT, light0Ka);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, light0Kd);
        glLightfv(GL_LIGHT0, GL_SPECULAR, light0Ks);
        // position the light
        float lightPos[4] = {0, 1.5, -1, 1};
        glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
        glEnable(GL_LIGHT0);  // MUST enable each light source after configuration

        GLfloat light1Ka[] = {0.3f, 0.0f, 0.9f, 1.0f};   // ambient light
        GLfloat light1Kd[] = {0.3f, 0.0f, 0.9f, 1.0f};   // diffuse light
        GLfloat light1Ks[] = {0.3f, 0.0f, 0.9f, 1.0f};   // specular light
        glLightfv(GL_LIGHT1, GL_AMBIENT, light1Ka);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, light1Kd);
        glLightfv(GL_LIGHT1, GL_SPECULAR, light1Ks);
        // position the light
        float light1Pos[4] = {0.0f, 0.0f, -1.0f, 0};
        glLightfv(GL_LIGHT1, GL_POSITION, light1Pos);
        glEnable(GL_LIGHT1);  // MUST enable each light source after configuration
    }
    else if (strcmp(OPTION, "2.bltr") == 0) {
        printf("OPTION: %s\n", OPTION);
        glEnable(GL_LIGHTING);
        // set up light colors (ambient, diffuse, specular)
        GLfloat light0Ka[] = {0.8f, 0.8f, 0.8f, 1.0f};   // ambient light
        GLfloat light0Kd[] = {0.8f, 0.8f, 0.8f, 1.0f};   // diffuse light
        GLfloat light0Ks[] = {0.8f, 0.8f, 0.8f, 1.0f};   // specular light
        glLightfv(GL_LIGHT0, GL_AMBIENT, light0Ka);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, light0Kd);
        glLightfv(GL_LIGHT0, GL_SPECULAR, light0Ks);
        // position the light
        float lightPos[4] = {0, 1.5, -1, 1};
        glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
        glEnable(GL_LIGHT0);  // MUST enable each light source after configuration

        GLfloat light1Ka[] = {0.3f, 0.0f, 0.9f, 1.0f};   // ambient light
        GLfloat light1Kd[] = {0.3f, 0.0f, 0.9f, 1.0f};   // diffuse light
        GLfloat light1Ks[] = {0.3f, 0.0f, 0.9f, 1.0f};   // specular light
        glLightfv(GL_LIGHT1, GL_AMBIENT, light1Ka);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, light1Kd);
        glLightfv(GL_LIGHT1, GL_SPECULAR, light1Ks);
        // position the light
        float light1Pos[4] = {-1.0f, -1.0f, 0.0f, 0};
        glLightfv(GL_LIGHT1, GL_POSITION, light1Pos);
        glEnable(GL_LIGHT1);  // MUST enable each light source after configuration
    }
    else if (strcmp(OPTION, "2.trbl") == 0) {
        printf("OPTION: %s\n", OPTION);
        glEnable(GL_LIGHTING);
        // set up light colors (ambient, diffuse, specular)
        GLfloat light0Ka[] = {0.8f, 0.8f, 0.8f, 1.0f};   // ambient light
        GLfloat light0Kd[] = {0.8f, 0.8f, 0.8f, 1.0f};   // diffuse light
        GLfloat light0Ks[] = {0.8f, 0.8f, 0.8f, 1.0f};   // specular light
        glLightfv(GL_LIGHT0, GL_AMBIENT, light0Ka);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, light0Kd);
        glLightfv(GL_LIGHT0, GL_SPECULAR, light0Ks);
        // position the light
        float lightPos[4] = {0, 1.5, -1, 1};
        glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
        glEnable(GL_LIGHT0);  // MUST enable each light source after configuration

        GLfloat light1Ka[] = {0.3f, 0.0f, 0.9f, 1.0f};   // ambient light
        GLfloat light1Kd[] = {0.3f, 0.0f, 0.9f, 1.0f};   // diffuse light
        GLfloat light1Ks[] = {0.3f, 0.0f, 0.9f, 1.0f};   // specular light
        glLightfv(GL_LIGHT1, GL_AMBIENT, light1Ka);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, light1Kd);
        glLightfv(GL_LIGHT1, GL_SPECULAR, light1Ks);
        // position the light
        float light1Pos[4] = {1.0f, 1.0f, 0.0f, 0};
        glLightfv(GL_LIGHT1, GL_POSITION, light1Pos);
        glEnable(GL_LIGHT1);  // MUST enable each light source after configuration
    }
    else if (strcmp(OPTION, "2.lra") == 0) {
        printf("OPTION: %s\n", OPTION);
        glEnable(GL_LIGHTING);
        // set up light colors (ambient, diffuse, specular)
        GLfloat light0Ka[] = {0.8f, 0.8f, 0.8f, 1.0f};   // ambient light
        GLfloat light0Kd[] = {0.8f, 0.8f, 0.8f, 1.0f};   // diffuse light
        GLfloat light0Ks[] = {0.8f, 0.8f, 0.8f, 1.0f};   // specular light
        glLightfv(GL_LIGHT0, GL_AMBIENT, light0Ka);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, light0Kd);
        glLightfv(GL_LIGHT0, GL_SPECULAR, light0Ks);
        // position the light
        float lightPos[4] = {0, 1.5, -1, 1};
        glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
        glEnable(GL_LIGHT0);  // MUST enable each light source after configuration

        GLfloat light1Ka[] = {0.0f, 1.0f, 0.0f, 1.0f};   // ambient light
        GLfloat light1Kd[] = {0.3f, 0.0f, 0.9f, 1.0f};   // diffuse light
        GLfloat light1Ks[] = {0.3f, 0.0f, 0.9f, 1.0f};   // specular light
        glLightfv(GL_LIGHT1, GL_AMBIENT, light1Ka);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, light1Kd);
        glLightfv(GL_LIGHT1, GL_SPECULAR, light1Ks);
        // position the light
        float light1Pos[4] = {-1.0f, 0.0f, 0.0f, 0};
        glLightfv(GL_LIGHT1, GL_POSITION, light1Pos);
        glEnable(GL_LIGHT1);  // MUST enable each light source after configuration
    }
    else if (strcmp(OPTION, "2.lrd") == 0) {
        printf("OPTION: %s\n", OPTION);
        glEnable(GL_LIGHTING);
        // set up light colors (ambient, diffuse, specular)
        GLfloat light0Ka[] = {0.8f, 0.8f, 0.8f, 1.0f};   // ambient light
        GLfloat light0Kd[] = {0.8f, 0.8f, 0.8f, 1.0f};   // diffuse light
        GLfloat light0Ks[] = {0.8f, 0.8f, 0.8f, 1.0f};   // specular light
        glLightfv(GL_LIGHT0, GL_AMBIENT, light0Ka);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, light0Kd);
        glLightfv(GL_LIGHT0, GL_SPECULAR, light0Ks);
        // position the light
        float lightPos[4] = {0, 1.5, -1, 1};
        glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
        glEnable(GL_LIGHT0);  // MUST enable each light source after configuration

        GLfloat light1Ka[] = {0.3f, 0.0f, 0.9f, 1.0f};   // ambient light
        GLfloat light1Kd[] = {0.0f, 1.0f, 0.0f, 1.0f};   // diffuse light
        GLfloat light1Ks[] = {0.3f, 0.0f, 0.9f, 1.0f};   // specular light
        glLightfv(GL_LIGHT1, GL_AMBIENT, light1Ka);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, light1Kd);
        glLightfv(GL_LIGHT1, GL_SPECULAR, light1Ks);
        // position the light
        float light1Pos[4] = {-1.0f, 0.0f, 0.0f, 0};
        glLightfv(GL_LIGHT1, GL_POSITION, light1Pos);
        glEnable(GL_LIGHT1);  // MUST enable each light source after configuration
    }
    else if (strcmp(OPTION, "2.lrs") == 0) {
        printf("OPTION: %s\n", OPTION);
        glEnable(GL_LIGHTING);
        // set up light colors (ambient, diffuse, specular)
        GLfloat light0Ka[] = {0.8f, 0.8f, 0.8f, 1.0f};   // ambient light
        GLfloat light0Kd[] = {0.8f, 0.8f, 0.8f, 1.0f};   // diffuse light
        GLfloat light0Ks[] = {0.8f, 0.8f, 0.8f, 1.0f};   // specular light
        glLightfv(GL_LIGHT0, GL_AMBIENT, light0Ka);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, light0Kd);
        glLightfv(GL_LIGHT0, GL_SPECULAR, light0Ks);
        // position the light
        float lightPos[4] = {0, 1.5, -1, 1};
        glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
        glEnable(GL_LIGHT0);  // MUST enable each light source after configuration

        GLfloat light1Ka[] = {0.3f, 0.0f, 0.9f, 1.0f};   // ambient light
        GLfloat light1Kd[] = {0.3f, 0.0f, 0.9f, 1.0f};   // diffuse light
        GLfloat light1Ks[] = {0.0f, 1.0f, 0.0f, 1.0f};   // specular light
        glLightfv(GL_LIGHT1, GL_AMBIENT, light1Ka);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, light1Kd);
        glLightfv(GL_LIGHT1, GL_SPECULAR, light1Ks);
        // position the light
        float light1Pos[4] = {-1.0f, 0.0f, 0.0f, 0};
        glLightfv(GL_LIGHT1, GL_POSITION, light1Pos);
        glEnable(GL_LIGHT1);  // MUST enable each light source after configuration
    }
    else if (strcmp(OPTION, "2.lrblue") == 0) {
        printf("OPTION: %s\n", OPTION);
        glEnable(GL_LIGHTING);
        // set up light colors (ambient, diffuse, specular)
        GLfloat light0Ka[] = {0.8f, 0.8f, 0.8f, 1.0f};   // ambient light
        GLfloat light0Kd[] = {0.8f, 0.8f, 0.8f, 1.0f};   // diffuse light
        GLfloat light0Ks[] = {0.8f, 0.8f, 0.8f, 1.0f};   // specular light
        glLightfv(GL_LIGHT0, GL_AMBIENT, light0Ka);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, light0Kd);
        glLightfv(GL_LIGHT0, GL_SPECULAR, light0Ks);
        // position the light
        float lightPos[4] = {0, 1.5, -1, 1};
        glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
        glEnable(GL_LIGHT0);  // MUST enable each light source after configuration

        GLfloat light1Ka[] = {0.0f, 0.0f, 1.0f, 1.0f};   // ambient light
        GLfloat light1Kd[] = {0.0f, 0.0f, 1.0f, 1.0f};   // diffuse light
        GLfloat light1Ks[] = {0.0f, 0.0f, 1.0f, 1.0f};   // specular light
        glLightfv(GL_LIGHT1, GL_AMBIENT, light1Ka);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, light1Kd);
        glLightfv(GL_LIGHT1, GL_SPECULAR, light1Ks);
        // position the light
        float light1Pos[4] = {-1.0f, 0.0f, 0.0f, 0};
        glLightfv(GL_LIGHT1, GL_POSITION, light1Pos);
        glEnable(GL_LIGHT1);  // MUST enable each light source after configuration
    }
    else if (strcmp(OPTION, "3") == 0) {
        printf("OPTION: %s\n", OPTION);
        glEnable(GL_LIGHTING);
        GLfloat newAmbient[4] = {0.2f, 0.2f, 0.2f, 1.0f};
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, newAmbient);
        GLfloat light3Ka[] = {0.8f, 0.8f, 0.8f, 1.0f};   // ambient light
        GLfloat light3Kd[] = {0.8f, 0.8f, 0.8f, 1.0f};   // diffuse light
        GLfloat light3Ks[] = {0.8f, 0.8f, 0.8f, 1.0f};   // specular light
        glLightfv(GL_LIGHT3, GL_AMBIENT, light3Ka);
        glLightfv(GL_LIGHT3, GL_DIFFUSE, light3Kd);
        glLightfv(GL_LIGHT3, GL_SPECULAR, light3Ks);
        // position the light
        GLfloat light3Pos[4] = {-2.0f, 1.0f, 0.0f, 1};
        glLightfv(GL_LIGHT3, GL_POSITION, light3Pos);
        glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 45.0f);
        glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, 20.0f);
        glLightf(GL_LIGHT3, GL_CONSTANT_ATTENUATION, 2.0f);
        // glEnable(GL_LIGHT3);  // MUST enable each light source after configuration
    }
    else if (strcmp(OPTION, "3a") == 0) {
        printf("OPTION: %s\n", OPTION);
        glEnable(GL_LIGHTING);
        GLfloat newAmbient[4] = {0.2f, 0.2f, 0.2f, 1.0f};
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, newAmbient);
        GLfloat light3Ka[] = {0.8f, 0.8f, 0.8f, 1.0f};   // ambient light
        GLfloat light3Kd[] = {0.8f, 0.8f, 0.8f, 1.0f};   // diffuse light
        GLfloat light3Ks[] = {0.8f, 0.8f, 0.8f, 1.0f};   // specular light
        glLightfv(GL_LIGHT3, GL_AMBIENT, light3Ka);
        glLightfv(GL_LIGHT3, GL_DIFFUSE, light3Kd);
        glLightfv(GL_LIGHT3, GL_SPECULAR, light3Ks);
        // position the light
        GLfloat light3Pos[4] = {-2.0f, 1.0f, 0.0f, 1};
        GLfloat light3Dir[4] = {0.0f, 0.0f, -1.0f, 1};
        glLightfv(GL_LIGHT3, GL_POSITION, light3Pos);
        glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, light3Dir);
        glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 45.0f);
        glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, 20.0f);
        glLightf(GL_LIGHT3, GL_CONSTANT_ATTENUATION, 2.0f);
        glEnable(GL_LIGHT3);  // MUST enable each light source after configuration
    }
    else if (strcmp(OPTION, "3az0") == 0) {
        printf("OPTION: %s\n", OPTION);
        glEnable(GL_LIGHTING);
        GLfloat newAmbient[4] = {0.2f, 0.2f, 0.2f, 1.0f};
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, newAmbient);
        GLfloat light3Ka[] = {0.8f, 0.8f, 0.8f, 1.0f};   // ambient light
        GLfloat light3Kd[] = {0.8f, 0.8f, 0.8f, 1.0f};   // diffuse light
        GLfloat light3Ks[] = {0.8f, 0.8f, 0.8f, 1.0f};   // specular light
        glLightfv(GL_LIGHT3, GL_AMBIENT, light3Ka);
        glLightfv(GL_LIGHT3, GL_DIFFUSE, light3Kd);
        glLightfv(GL_LIGHT3, GL_SPECULAR, light3Ks);
        // position the light
        GLfloat light3Pos[4] = {-2.0f, 1.0f, 0.0f, 1};
        GLfloat light3Dir[4] = {0.0f, 0.0f, -1.0f, 1};
        glLightfv(GL_LIGHT3, GL_POSITION, light3Pos);
        glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, light3Dir);
        glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 45.0f);
        glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, 20.0f);
        glLightf(GL_LIGHT3, GL_CONSTANT_ATTENUATION, 2.0f);
        glEnable(GL_LIGHT3);  // MUST enable each light source after configuration
    }
    else if (strcmp(OPTION, "3az1") == 0) {
        printf("OPTION: %s\n", OPTION);
        glEnable(GL_LIGHTING);
        GLfloat newAmbient[4] = {0.2f, 0.2f, 0.2f, 1.0f};
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, newAmbient);
        GLfloat light3Ka[] = {0.8f, 0.8f, 0.8f, 1.0f};   // ambient light
        GLfloat light3Kd[] = {0.8f, 0.8f, 0.8f, 1.0f};   // diffuse light
        GLfloat light3Ks[] = {0.8f, 0.8f, 0.8f, 1.0f};   // specular light
        glLightfv(GL_LIGHT3, GL_AMBIENT, light3Ka);
        glLightfv(GL_LIGHT3, GL_DIFFUSE, light3Kd);
        glLightfv(GL_LIGHT3, GL_SPECULAR, light3Ks);
        // position the light
        GLfloat light3Pos[4] = {-2.0f, 1.0f, -1.0f, 1};
        GLfloat light3Dir[4] = {0.0f, 0.0f, -1.0f, 1};
        glLightfv(GL_LIGHT3, GL_POSITION, light3Pos);
        glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, light3Dir);
        glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 45.0f);
        glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, 20.0f);
        glLightf(GL_LIGHT3, GL_CONSTANT_ATTENUATION, 2.0f);
        glEnable(GL_LIGHT3);  // MUST enable each light source after configuration
    }
    else if (strcmp(OPTION, "3az2") == 0) {
        printf("OPTION: %s\n", OPTION);
        glEnable(GL_LIGHTING);
        GLfloat newAmbient[4] = {0.2f, 0.2f, 0.2f, 1.0f};
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, newAmbient);
        GLfloat light3Ka[] = {0.8f, 0.8f, 0.8f, 1.0f};   // ambient light
        GLfloat light3Kd[] = {0.8f, 0.8f, 0.8f, 1.0f};   // diffuse light
        GLfloat light3Ks[] = {0.8f, 0.8f, 0.8f, 1.0f};   // specular light
        glLightfv(GL_LIGHT3, GL_AMBIENT, light3Ka);
        glLightfv(GL_LIGHT3, GL_DIFFUSE, light3Kd);
        glLightfv(GL_LIGHT3, GL_SPECULAR, light3Ks);
        // position the light
        GLfloat light3Pos[4] = {-2.0f, 1.0f, -2.0f, 1};
        GLfloat light3Dir[4] = {0.0f, 0.0f, -1.0f, 1};
        glLightfv(GL_LIGHT3, GL_POSITION, light3Pos);
        glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, light3Dir);
        glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 45.0f);
        glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, 20.0f);
        glLightf(GL_LIGHT3, GL_CONSTANT_ATTENUATION, 2.0f);
        glEnable(GL_LIGHT3);  // MUST enable each light source after configuration
    }
    else if (strcmp(OPTION, "3az3") == 0) {
        printf("OPTION: %s\n", OPTION);
        glEnable(GL_LIGHTING);
        GLfloat newAmbient[4] = {0.2f, 0.2f, 0.2f, 1.0f};
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, newAmbient);
        GLfloat light3Ka[] = {0.8f, 0.8f, 0.8f, 1.0f};   // ambient light
        GLfloat light3Kd[] = {0.8f, 0.8f, 0.8f, 1.0f};   // diffuse light
        GLfloat light3Ks[] = {0.8f, 0.8f, 0.8f, 1.0f};   // specular light
        glLightfv(GL_LIGHT3, GL_AMBIENT, light3Ka);
        glLightfv(GL_LIGHT3, GL_DIFFUSE, light3Kd);
        glLightfv(GL_LIGHT3, GL_SPECULAR, light3Ks);
        // position the light
        GLfloat light3Pos[4] = {-2.0f, 1.0f, -3.0f, 1};
        GLfloat light3Dir[4] = {0.0f, 0.0f, -1.0f, 1};
        glLightfv(GL_LIGHT3, GL_POSITION, light3Pos);
        glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, light3Dir);
        glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 45.0f);
        glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, 20.0f);
        glLightf(GL_LIGHT3, GL_CONSTANT_ATTENUATION, 2.0f);
        glEnable(GL_LIGHT3);  // MUST enable each light source after configuration
    }
    else if (strcmp(OPTION, "3b5") == 0) {
        printf("OPTION: %s\n", OPTION);
        glEnable(GL_LIGHTING);
        GLfloat newAmbient[4] = {0.2f, 0.2f, 0.2f, 1.0f};
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, newAmbient);
        GLfloat light3Ka[] = {0.8f, 0.8f, 0.8f, 1.0f};   // ambient light
        GLfloat light3Kd[] = {0.8f, 0.8f, 0.8f, 1.0f};   // diffuse light
        GLfloat light3Ks[] = {0.8f, 0.8f, 0.8f, 1.0f};   // specular light
        glLightfv(GL_LIGHT3, GL_AMBIENT, light3Ka);
        glLightfv(GL_LIGHT3, GL_DIFFUSE, light3Kd);
        glLightfv(GL_LIGHT3, GL_SPECULAR, light3Ks);
        // position the light
        GLfloat light3Pos[4] = {-2.0f, 1.0f, 0.0f, 1};
        GLfloat light3Dir[4] = {0.0f, 0.0f, -1.0f, 1};
        glLightfv(GL_LIGHT3, GL_POSITION, light3Pos);
        glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, light3Dir);
        glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 5.0f);
        glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, 20.0f);
        glLightf(GL_LIGHT3, GL_CONSTANT_ATTENUATION, 2.0f);
        glEnable(GL_LIGHT3);  // MUST enable each light source after configuration
    }
    else if (strcmp(OPTION, "3b3") == 0) {
        printf("OPTION: %s\n", OPTION);
        glEnable(GL_LIGHTING);
        GLfloat newAmbient[4] = {0.2f, 0.2f, 0.2f, 1.0f};
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, newAmbient);
        GLfloat light3Ka[] = {0.8f, 0.8f, 0.8f, 1.0f};   // ambient light
        GLfloat light3Kd[] = {0.8f, 0.8f, 0.8f, 1.0f};   // diffuse light
        GLfloat light3Ks[] = {0.8f, 0.8f, 0.8f, 1.0f};   // specular light
        glLightfv(GL_LIGHT3, GL_AMBIENT, light3Ka);
        glLightfv(GL_LIGHT3, GL_DIFFUSE, light3Kd);
        glLightfv(GL_LIGHT3, GL_SPECULAR, light3Ks);
        // position the light
        GLfloat light3Pos[4] = {-2.0f, 1.0f, 0.0f, 1};
        GLfloat light3Dir[4] = {0.0f, 0.0f, -1.0f, 1};
        glLightfv(GL_LIGHT3, GL_POSITION, light3Pos);
        glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, light3Dir);
        glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 3.0f);
        glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, 20.0f);
        glLightf(GL_LIGHT3, GL_CONSTANT_ATTENUATION, 2.0f);
        glEnable(GL_LIGHT3);  // MUST enable each light source after configuration
    }
    else if (strcmp(OPTION, "3c") == 0) {
        printf("OPTION: %s\n", OPTION);
        glEnable(GL_LIGHTING);
        GLfloat newAmbient[4] = {0.2f, 0.2f, 0.2f, 1.0f};
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, newAmbient);
        GLfloat light3Ka[] = {0.8f, 0.8f, 0.8f, 1.0f};   // ambient light
        GLfloat light3Kd[] = {0.8f, 0.8f, 0.8f, 1.0f};   // diffuse light
        GLfloat light3Ks[] = {0.8f, 0.8f, 0.8f, 1.0f};   // specular light
        glLightfv(GL_LIGHT3, GL_AMBIENT, light3Ka);
        glLightfv(GL_LIGHT3, GL_DIFFUSE, light3Kd);
        glLightfv(GL_LIGHT3, GL_SPECULAR, light3Ks);
        // position the light
        GLfloat light3Pos[4] = {-2.0f, 1.0f, 0.0f, 1};
        GLfloat light3Dir[4] = {-0.03f, 0.06f, -1.0f, 1};
        glLightfv(GL_LIGHT3, GL_POSITION, light3Pos);
        glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, light3Dir);
        glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 3.0f);
        glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, 20.0f);
        glLightf(GL_LIGHT3, GL_CONSTANT_ATTENUATION, 2.0f);
        glEnable(GL_LIGHT3);  // MUST enable each light source after configuration
    }
    else if (strcmp(OPTION, "3d5") == 0) {
        printf("OPTION: %s\n", OPTION);
        glEnable(GL_LIGHTING);
        GLfloat newAmbient[4] = {0.2f, 0.2f, 0.2f, 1.0f};
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, newAmbient);
        GLfloat light3Ka[] = {0.8f, 0.8f, 0.8f, 1.0f};   // ambient light
        GLfloat light3Kd[] = {0.8f, 0.8f, 0.8f, 1.0f};   // diffuse light
        GLfloat light3Ks[] = {0.8f, 0.8f, 0.8f, 1.0f};   // specular light
        glLightfv(GL_LIGHT3, GL_AMBIENT, light3Ka);
        glLightfv(GL_LIGHT3, GL_DIFFUSE, light3Kd);
        glLightfv(GL_LIGHT3, GL_SPECULAR, light3Ks);
        // position the light
        GLfloat light3Pos[4] = {-2.0f, 1.0f, 0.0f, 1};
        GLfloat light3Dir[4] = {-0.03f, 0.06f, -1.0f, 1};
        glLightfv(GL_LIGHT3, GL_POSITION, light3Pos);
        glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, light3Dir);
        glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 3.0f);
        glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, 20.0f);
        glLightf(GL_LIGHT3, GL_CONSTANT_ATTENUATION, 5.0f);
        glEnable(GL_LIGHT3);  // MUST enable each light source after configuration
    }
    else if (strcmp(OPTION, "3d1") == 0) {
        printf("OPTION: %s\n", OPTION);
        glEnable(GL_LIGHTING);
        GLfloat newAmbient[4] = {0.2f, 0.2f, 0.2f, 1.0f};
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, newAmbient);
        GLfloat light3Ka[] = {0.8f, 0.8f, 0.8f, 1.0f};   // ambient light
        GLfloat light3Kd[] = {0.8f, 0.8f, 0.8f, 1.0f};   // diffuse light
        GLfloat light3Ks[] = {0.8f, 0.8f, 0.8f, 1.0f};   // specular light
        glLightfv(GL_LIGHT3, GL_AMBIENT, light3Ka);
        glLightfv(GL_LIGHT3, GL_DIFFUSE, light3Kd);
        glLightfv(GL_LIGHT3, GL_SPECULAR, light3Ks);
        // position the light
        GLfloat light3Pos[4] = {-2.0f, 1.0f, 0.0f, 1};
        GLfloat light3Dir[4] = {-0.03f, 0.06f, -1.0f, 1};
        glLightfv(GL_LIGHT3, GL_POSITION, light3Pos);
        glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, light3Dir);
        glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 3.0f);
        glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, 20.0f);
        glLightf(GL_LIGHT3, GL_CONSTANT_ATTENUATION, 1.0f);
        glEnable(GL_LIGHT3);  // MUST enable each light source after configuration
    }
    else if (strcmp(OPTION, "4") == 0) {
        // Problem 4 Lighting
        printf("OPTION: %s\n", OPTION);
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
    else if (strcmp(OPTION, "4") == 0
            || strcmp(OPTION, "4aa1") == 0
            || strcmp(OPTION, "4aa2") == 0
            || strcmp(OPTION, "4aa3") == 0
            || strcmp(OPTION, "4ad1") == 0
            || strcmp(OPTION, "4ad2") == 0
            || strcmp(OPTION, "4ad3") == 0
            || strcmp(OPTION, "4as1") == 0
            || strcmp(OPTION, "4as2") == 0
            || strcmp(OPTION, "4as3") == 0
            || strcmp(OPTION, "4ash1") == 0
            || strcmp(OPTION, "4ash2") == 0
            || strcmp(OPTION, "4ash3") == 0
            || strcmp(OPTION, "4ash4") == 0) {
        printf("OPTION: %s\n", OPTION);
        glEnable(GL_LIGHTING);
        GLfloat light1Ka[] = {1.0f, 1.0f, 1.0f, 1.0f};   // ambient light
        GLfloat light1Kd[] = {1.0f, 1.0f, 1.0f, 1.0f};   // diffuse light
        GLfloat light1Ks[] = {1.0f, 1.0f, 1.0f, 1.0f};   // specular light
        glLightfv(GL_LIGHT1, GL_AMBIENT, light1Ka);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, light1Kd);
        glLightfv(GL_LIGHT1, GL_SPECULAR, light1Ks);
        GLfloat light1Pos[4] = {0.0f, 0.0f, 0.0f, 1};
        glLightfv(GL_LIGHT1, GL_POSITION, light1Pos);
        glEnable(GL_LIGHT1);  // MUST enable each light source after configuration
    }
    else if (strcmp(OPTION, "4") == 0
            || strcmp(OPTION, "4b1a1") == 0
            || strcmp(OPTION, "4b1a2") == 0
            || strcmp(OPTION, "4b1a3") == 0
            || strcmp(OPTION, "4b1d1") == 0
            || strcmp(OPTION, "4b1d2") == 0
            || strcmp(OPTION, "4b1d3") == 0
            || strcmp(OPTION, "4b1s1") == 0
            || strcmp(OPTION, "4b1s2") == 0
            || strcmp(OPTION, "4b1s3") == 0
            || strcmp(OPTION, "4b1sh1") == 0
            || strcmp(OPTION, "4b1sh2") == 0
            || strcmp(OPTION, "4b1sh3") == 0
            || strcmp(OPTION, "4b1sh4") == 0) {
        printf("OPTION: %s\n", OPTION);
        glEnable(GL_LIGHTING);
        GLfloat light1Ka[] = {1.0f, 1.0f, 1.0f, 0.4f};   // ambient light
        GLfloat light1Kd[] = {1.0f, 1.0f, 1.0f, 0.4f};   // diffuse light
        GLfloat light1Ks[] = {1.0f, 1.0f, 1.0f, 0.4f};   // specular light
        glLightfv(GL_LIGHT1, GL_AMBIENT, light1Ka);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, light1Kd);
        glLightfv(GL_LIGHT1, GL_SPECULAR, light1Ks);
        GLfloat light1Pos[4] = {0.0f, 0.0f, 0.0f, 1};
        glLightfv(GL_LIGHT1, GL_POSITION, light1Pos);
        glEnable(GL_LIGHT1);  // MUST enable each light source after configuration

        GLfloat light2Ka[] = {1.0f, 0.0f, 0.0f, 0.3f};   // ambient light
        GLfloat light2Kd[] = {1.0f, 0.0f, 0.0f, 0.3f};   // diffuse light
        GLfloat light2Ks[] = {1.0f, 1.0f, 1.0f, 0.3f};   // specular light
        glLightfv(GL_LIGHT2, GL_AMBIENT, light2Ka);
        glLightfv(GL_LIGHT2, GL_DIFFUSE, light2Kd);
        glLightfv(GL_LIGHT2, GL_SPECULAR, light2Ks);
        GLfloat light2Pos[4] = {0.0f, 0.0f, 1.0f, 1};
        glLightfv(GL_LIGHT2, GL_POSITION, light2Pos);
        glEnable(GL_LIGHT2);
    }
    else if (strcmp(OPTION, "4") == 0
            || strcmp(OPTION, "4b2a1") == 0
            || strcmp(OPTION, "4b2a2") == 0
            || strcmp(OPTION, "4b2a3") == 0
            || strcmp(OPTION, "4b2d1") == 0
            || strcmp(OPTION, "4b2d2") == 0
            || strcmp(OPTION, "4b2d3") == 0
            || strcmp(OPTION, "4b2s1") == 0
            || strcmp(OPTION, "4b2s2") == 0
            || strcmp(OPTION, "4b2s3") == 0
            || strcmp(OPTION, "4b2sh1") == 0
            || strcmp(OPTION, "4b2sh2") == 0
            || strcmp(OPTION, "4b2sh3") == 0
            || strcmp(OPTION, "4b2sh4") == 0) {
        printf("OPTION: %s\n", OPTION);
        glEnable(GL_LIGHTING);
        GLfloat light1Ka[] = {1.0f, 1.0f, 1.0f, 0.4f};   // ambient light
        GLfloat light1Kd[] = {1.0f, 1.0f, 1.0f, 0.4f};   // diffuse light
        GLfloat light1Ks[] = {1.0f, 1.0f, 1.0f, 0.4f};   // specular light
        glLightfv(GL_LIGHT1, GL_AMBIENT, light1Ka);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, light1Kd);
        glLightfv(GL_LIGHT1, GL_SPECULAR, light1Ks);
        GLfloat light1Pos[4] = {0.0f, 0.0f, 1.0f, 1};
        glLightfv(GL_LIGHT1, GL_POSITION, light1Pos);
        glEnable(GL_LIGHT1);

        GLfloat light2Ka[] = {0.0f, 1.0f, 0.0f, 0.3f};   // ambient light
        GLfloat light2Kd[] = {0.0f, 1.0f, 0.0f, 0.3f};   // diffuse light
        GLfloat light2Ks[] = {1.0f, 1.0f, 1.0f, 0.3f};   // specular light
        glLightfv(GL_LIGHT2, GL_AMBIENT, light2Ka);
        glLightfv(GL_LIGHT2, GL_DIFFUSE, light2Kd);
        glLightfv(GL_LIGHT2, GL_SPECULAR, light2Ks);
        GLfloat light2Pos[4] = {1.0f, 0.0f, 1.0f, 1};
        glLightfv(GL_LIGHT2, GL_POSITION, light2Pos);
        glEnable(GL_LIGHT2);
    }
    else if (strcmp(OPTION, "4") == 0
            || strcmp(OPTION, "4b3a1") == 0
            || strcmp(OPTION, "4b3a2") == 0
            || strcmp(OPTION, "4b3a3") == 0
            || strcmp(OPTION, "4b3d1") == 0
            || strcmp(OPTION, "4b3d2") == 0
            || strcmp(OPTION, "4b3d3") == 0
            || strcmp(OPTION, "4b3s1") == 0
            || strcmp(OPTION, "4b3s2") == 0
            || strcmp(OPTION, "4b3s3") == 0
            || strcmp(OPTION, "4b3sh1") == 0
            || strcmp(OPTION, "4b3sh2") == 0
            || strcmp(OPTION, "4b3sh3") == 0
            || strcmp(OPTION, "4b3sh4") == 0) {
        printf("OPTION: %s\n", OPTION);
        glEnable(GL_LIGHTING);
        GLfloat light1Ka[] = {1.0f, 1.0f, 1.0f, 0.4f};   // ambient light
        GLfloat light1Kd[] = {1.0f, 1.0f, 1.0f, 0.4f};   // diffuse light
        GLfloat light1Ks[] = {1.0f, 1.0f, 1.0f, 0.4f};   // specular light
        glLightfv(GL_LIGHT1, GL_AMBIENT, light1Ka);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, light1Kd);
        glLightfv(GL_LIGHT1, GL_SPECULAR, light1Ks);
        GLfloat light1Pos[4] = {0.0f, 0.0f, 0.0f, 1};
        glLightfv(GL_LIGHT1, GL_POSITION, light1Pos);
        glEnable(GL_LIGHT1);  // MUST enable each light source after configuration

        GLfloat light2Ka[] = {0.5f, 0.5f, 1.0f, 0.3f};   // ambient light
        GLfloat light2Kd[] = {0.5f, 0.5f, 1.0f, 0.3f};   // diffuse light
        GLfloat light2Ks[] = {1.0f, 1.0f, 1.0f, 0.3f};   // specular light
        glLightfv(GL_LIGHT2, GL_AMBIENT, light2Ka);
        glLightfv(GL_LIGHT2, GL_DIFFUSE, light2Kd);
        glLightfv(GL_LIGHT2, GL_SPECULAR, light2Ks);
        GLfloat light2Pos[4] = {0.0f, 0.0f, 1.0f, 1};
        glLightfv(GL_LIGHT2, GL_POSITION, light2Pos);
        glEnable(GL_LIGHT2);
    }
    else {
        printf("OPTION: %s\n", OPTION);
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
}

//<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB );
    glutInitWindowSize(640,480);
    glutInitWindowPosition(100, 100);
    char title[] = "Materials and Lighting tested - ";
    glutCreateWindow(strcat(title, OPTION));
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

