// main.cpp
// COSC 5450 Project 4: Gaming - Fishing
// Libao Jin <ljin1@uwyo.edu>
// Updated date: 11/30/2018

int const WIDTH = 800, HEIGHT = 600;
float const ASPECT = (float)WIDTH / HEIGHT;
float W = WIDTH / 2;
float H = HEIGHT / 2;

#include "header/color.h"
#include "header/fish.h"
#include "header/usefreeimage.h"
#include <climits>
#include <cstdlib>
#include <ctime>
#include <vector>

Color background(0.5, 0.5, 0.5, 1);
bool pause = false;
float foodSpeed = 10;
float fishSpeed = 10;
clock_t tic;
clock_t toc;
float timeElapsed;
// refresh time in milliseconds
float refreshTime = 500;
vector<Food> foods;
Fish fish(0, -H, 5, 0);

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

    tic = clock();
    srand(time(NULL));

    float new_x = (float)(rand() % WIDTH - W);
    Food food(new_x, H - 30, 4);
    foods.push_back(food);
}

// reference:
// https://www.opengl.org/discussion_boards/showthread.php/140785-Need-some-help-with-glutTimerFunc
// https://www.opengl.org/resources/libraries/glut/spec3/node64.html
void timer(int value)
{
    if (rand() % 100 > 80) {
        float new_x = (float)(rand() % WIDTH - W);
        Food food(new_x, H, 4);
        foods.push_back(food);
    }
    for (int i = 0; i < foods.size();) {
        foods[i].position.y -= foodSpeed;
        if (foods[i].position.y < -H) {
            foods.erase(foods.begin() + i);
            continue;
        }
        else if (foods[i].position.y - fish.position.y >= 0 &&
                 foods[i].position.y - fish.position.y <= 2 * fish.size &&
                 foods[i].position.x - fish.position.x >= 0 &&
                 foods[i].position.x - fish.position.x <= 3 * fish.size) {
            ++fish.size;
            foods.erase(foods.begin() + i);
            continue;
        }
        else {
            ++i;
        }
    }
    if (!pause) glutTimerFunc(refreshTime, timer, value);
    glutPostRedisplay();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(background.r, background.g, background.b, background.a);
    fish.draw();
    for (auto &f : foods) {
        f.draw();
    }
    if (USEFREEIMAGE) saveImage();
    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    // move fish to the left
    case 'H':
    case 'h':
        if (!pause) {
            fish.direction = 0;
            fish.move(-fishSpeed);
        }
        break;
    // move fish to the right
    case 'L':
    case 'l':
        if (!pause) {
            fish.direction = 1;
            fish.move(fishSpeed);
        }
        break;
    // press ESC key to exit
    case 'P':
    case 'p':
        pause = true;
        break;
    case 'S':
    case 's':
        if (pause) {
            pause = false;
            timer(1);
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

void special(int key, int x, int y)
{
    switch (key) {
    // use left arrow key to move fish to the left
    case GLUT_KEY_LEFT:
        if (!pause) {
            fish.direction = 0;
            fish.move(-fishSpeed);
        }
        break;
    // use right arrow key to move fish to the right
    case GLUT_KEY_RIGHT:
        if (!pause) {
            fish.direction = 1;
            fish.move(fishSpeed);
        }
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
    glutSpecialFunc(special);
    glutTimerFunc(refreshTime, timer, 1);
    glutMainLoop();
    return 0;
}
