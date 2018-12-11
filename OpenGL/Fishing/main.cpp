// main.cpp
// COSC 5450 Project 4: Gaming - Fishing
// Libao Jin <ljin1@uwyo.edu>
// Updated date: 12/10/2018

int const WIDTH = 800, HEIGHT = 600;
float const ASPECT = (float)WIDTH / HEIGHT;
float W = WIDTH / 2;
float H = HEIGHT / 2;

#include "header/fish.h"
#include "header/score.h"
#include "header/usefreeimage.h"
#include <climits>
#include <cstdlib>
#include <ctime>
#include <vector>

Color background(0.156862745, 0.368627451, 0.717647059, 1);
bool pause = false;
bool gameOver = false;
float foodSpeed = 20;
float fishSpeed = 20;
clock_t tic;
clock_t toc;
float timeElapsed;
float foodSize = 10;
Color healthyFoodColor(0.823529412, 0.839215686, 0.364705882, 1);
Color poisonousFoodColor(0.850980392, 0.631372549, 0.752941176, 1);
float initialFishSize = 8;
// refresh time in milliseconds
float refreshTime = 200;
vector<Food> foods;

Fish fish(0, -H, initialFishSize, 0, 5, 5, 0.956862745, 0.898039216, 0.301960784);
Score score(-W + 5, H - 20, 0, 3, 1, 1, 1);

void init() {
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
    Food food(new_x, H, foodSize, 0, healthyFoodColor);
    foods.push_back(food);
}

// reference:
// https://www.opengl.org/discussion_boards/showthread.php/140785-Need-some-help-with-glutTimerFunc
// https://www.opengl.org/resources/libraries/glut/spec3/node64.html
void timer(int value) {
    if (rand() % 100 > 80) {
        float new_x = (float)(rand() % WIDTH - W);
        float type = (float)(rand() % 2);
        if (type == 0) {
            Food food(new_x, H, foodSize, type, healthyFoodColor);
            foods.push_back(food);
        } else {
            Food food(new_x, H, foodSize, type, poisonousFoodColor);
            foods.push_back(food);
        }
    }
    for (int i = 0; i < foods.size();) {
        foods[i].position.y -= foodSpeed;
        if (foods[i].position.y < -H) {
            foods.erase(foods.begin() + i);
            continue;
        } else if (foods[i].position.y - fish.position.y >= -(fish.height * fish.size + foods[i].height * foods[i].size / 2) &&
                   foods[i].position.y - fish.position.y <= fish.height * fish.size + foods[i].height * foods[i].size / 2 &&
                   foods[i].position.x - fish.position.x >= -(fish.width / 2 * fish.size + foods[i].width / 2 * foods[i].size) &&
                   foods[i].position.x - fish.position.x <= fish.width / 2 * fish.size + foods[i].width / 2 * foods[i].size) {
            if (foods[i].type == 0) {
                ++fish.size;
                ++score.score;
            } else {
                --fish.size;
                --score.score;
                if (--score.healthPoints <= 0)
                    gameOver = true;
            }
            foods.erase(foods.begin() + i);
            continue;
        } else {
            ++i;
        }
    }
    if (!pause && !gameOver)
        glutTimerFunc(refreshTime, timer, value);
    glutPostRedisplay();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(background.r, background.g, background.b, background.a);
    if (!gameOver) {
        score.print();
        fish.draw();
        for (auto &f : foods)
            f.draw();
    } else {
        score.print(gameOver);
    }
    if (USEFREEIMAGE)
        saveImage();
    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    // move fish to the left
    case 'H':
    case 'h':
        if (!pause) {
            fish.direction = 0;
            fish.move(-fishSpeed);
            // make sure fish is in the screen
            if (fish.position.x < -W)
                fish.position.set(-W, fish.position.y);
        }
        break;
    // move fish to the right
    case 'L':
    case 'l':
        if (!pause) {
            fish.direction = 1;
            fish.move(fishSpeed);
            // make sure fish is in the screen
            if (fish.position.x + fish.size * fish.width / 2 > W)
                fish.position.set(W - fish.size * fish.width / 2, fish.position.y);
        }
        break;
    // press ESC key to exit
    case 'P':
    case 'p':
        pause = true;
        break;
    case 'R':
    case 'r':
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

void special(int key, int x, int y) {
    switch (key) {
    // use left arrow key to move fish to the left
    case GLUT_KEY_LEFT:
        if (!pause) {
            fish.direction = 0;
            fish.move(-fishSpeed);
            // make sure fish is in the screen
            if (fish.position.x - fish.size * fish.width / 2 < -W)
                fish.position.set(-W + fish.size * fish.width / 2, fish.position.y);
        }
        break;
    // use right arrow key to move fish to the right
    case GLUT_KEY_RIGHT:
        if (!pause) {
            fish.direction = 1;
            fish.move(fishSpeed);
            // make sure fish is in the screen
            if (fish.position.x + fish.size * fish.width / 2 > W)
                fish.position.set(W - fish.size * fish.width / 2, fish.position.y);
        }
        break;
    default:
        break;
    }
    glutPostRedisplay();
}

int main(int argc, char **argv) {
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
