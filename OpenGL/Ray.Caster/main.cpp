// main.cpp
// COSC 5450 Project 3a/3b/3c: RayCaster/RayShader/RayTracer
// Libao Jin
// ljin1@uwyo.edu
// Updated date: 11/19/2018

int const WIDTH = 500, HEIGHT = 400;
float const ASPECT = (float)WIDTH / HEIGHT;

#include "header/ray.h"
#include "header/usefreeimage.h"

// set parameters for the environment
bool isPerspectiveProjection = true;
bool addEmission = false;
float viewScreenWidth = 0.5;
float viewAngle = 32;
float W = viewScreenWidth / 2;
float H = W / ASPECT;
float N = H / tan((viewAngle / 2) / 180 * pi);
int blockSize[8] = {1, 2, 4, 5, 10, 20, 50, 100};
int blockIndex = 0;
int level = 3;
int levelCap = 8;
Point eye(0, 0, 1);
Point look(0, 0, 0);
Vector up(0, 1, 0);
Color backgroundColor(0.5, 0.5, 0.5);
// define spheres and a cylinder
Material m1(0.5, 0.5, 0.5, 1, 0.7, 0.7, 0.7, 1, 0.9, 0.9, 0.9, 1, 1, 0, 0, 1, 3);
Material m2(0.5, 0.5, 0.5, 1, 0.4, 0.4, 0.4, 1, 0.001, 0.001, 0.001, 1, 0, 1, 0, 1, 1);
Material m3(0.23125, 0.23125, 0.23125, 1, 0.2775, 0.2775, 0.2775, 1, 0.6, 0.6, 0.6, 1, 0, 0, 1, 1, 89.6);
Object o1("sphere", 0.125, 0.125, -0.25, -1, m1);
Object o2("sphere", 0.375, 0.5, 0.5, -1.75, m2);
Object o3("sphere", 0.75, -0.5, 0, -2.5, m3);
Object o4("cylinder", 0.15, 0.5, 0.25, -0.35, -1.125, 0, 1, 1);
// set parameters for lights
Light globalAmbient(0.25, 0.05, 0.05, 1);
Light pointLight(0.65, 0.65, 0.65, 1, 0, 0, 0, 1, 0, 0, 0, 1, 200, 100, 50, 1);
Light spotlight(0, 0, 0, 1, 0, 0, 0, 1, 0.4, 0.4, 0.7, 1, -1, 0, 1, 1, 0, 0, -1, 0, 30, 0.5);
Light yellowLight(0, 0, 0, 1, 0.8, 0.8, 0.6, 1, 0, 0, 0, 1, -400, 692, 0, 0);
// use STL vector to store objects and lights
vector<Object> objects;
vector<Light> lights;
RayCast raycaster;

void init()
{
    // add objects to the object list
    objects.push_back(o1);
    objects.push_back(o2);
    objects.push_back(o3);
    // objects.push_back(o4);

    // add lights to the light list
    lights.push_back(globalAmbient);
    lights.push_back(pointLight);
    lights.push_back(spotlight);
    lights.push_back(yellowLight);

    glViewport(0, 0, WIDTH, HEIGHT);
    gluOrtho2D(-W, W, -H, H);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // update the parameters for raycaster
    raycaster.set(backgroundColor, WIDTH, HEIGHT, blockSize[blockIndex], N, W, H, eye, look, up);
    // ray tracing and draw the pixmap
    raycaster.cast(objects, lights, level, isPerspectiveProjection, addEmission);

    if (USEFREEIMAGE) saveImage();
    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    // decrease blocksize to make the resolution of objects higher
    case 'h':
        if (--blockIndex <= 0) blockIndex = 0;
        break;
    // increase blocksize to make the resolution of objects lower
    case 'l':
        if (++blockIndex > 7) blockIndex = 7;
        break;
    case '-':
    // decrease reflection level
        if (--level <= 0) level = 0;
        break;
    case '+':
    // increase reflection level
        if (++level > levelCap) level = levelCap;
        break;
    case 'o':
    case 'O':
    // orthogonal projection
        isPerspectiveProjection = false;
        break;
    case 'p':
    case 'P':
    // perspective projection
        isPerspectiveProjection = true;
        break;
    case 'e':
    case 'E':
    // add/delete emission when do the ray tracing
        addEmission = !addEmission;
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
    if (strcmp(PROJECT, "proj3a") == 0)
        glutCreateWindow("COSC 5450 Project 3a: RayCaster by Libao Jin");
    else if (strcmp(PROJECT, "proj3b") == 0)
        glutCreateWindow("COSC 5450 Project 3b: RayShader by Libao Jin");
    else
        glutCreateWindow("COSC 5450 Project 3c: RayTracer by Libao Jin");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
