// main.cpp
// COSC 5450 Project 4: Gaming
// Libao Jin <ljin1@uwyo.edu>
// Updated date: 11/30/2018

int const WIDTH = 800, HEIGHT = 600;
float const ASPECT = (float)WIDTH / HEIGHT;

int W = WIDTH / 2;
int H = HEIGHT / 2;

#include "header/fish.h"
#include "header/color.h"
#include "header/usefreeimage.h"
#include <cstdlib>

Color background(0.5, 0.5, 0.5, 1);
Food food(40, 40, 2);
Fish fish(0, 0, 20);

void init()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(background.r, background.g, background.b, background.a);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport(0, 0, WIDTH, HEIGHT);
    gluOrtho2D(-W, W, -H, H);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(background.r, background.g, background.b, background.a);
    fish.draw();
    food.draw();
    if (USEFREEIMAGE) saveImage();
    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    // move fish to the right
    case 'L':
    case 'l':
        break;
    // move fish to the left
    case 'H':
    case 'h':
        break;
    // move fish upward
    case 'K':
    case 'k':
        break;
    // move fish downward
    case 'J':
    case 'j':
        break;
    // press ESC key to exit
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
    glutCreateWindow("COSC 5450 Project 4: Gaming by Libao Jin");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
