// fish.h
// Implementation for Fish and Food class
// COSC 5450 Project 4
// Libao Jin <ljin1@uwyo.edu>
// Updated date: 12/10/2018

#ifndef FISH_H
#define FISH_H

#if defined _WIN32 || defined WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
// #include <gl/glut.h>
#include "glut.h"
#elif defined __APPLE__ && !defined X11
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

#include "color.h"
#include "point.h"
#include <cmath>

using namespace std;

class Food;

class Fish {
  public:
    Point position;
    Color color;
    float size;
    float width;
    float height;
    int direction;

    Fish() {}

    Fish(float x, float y, float size, int direction, float width, float height) {
        this->position.set(x, y);
        this->size = size;
        this->direction = direction;
        this->width = width;
        this->height = height;
        this->color.set(1, 1, 1);
    }

    Fish(float x, float y, float size, int direction, float width, float height, float r, float g, float b) {
        this->position.set(x, y);
        this->size = size;
        this->direction = direction;
        this->width = width;
        this->height = height;
        this->color.set(r, g, b);
    }

    Fish(Point &position, float size, int direction, float width, float height) {
        this->position.set(position);
        this->size = size;
        this->direction = direction;
        this->width = width;
        this->height = height;
        this->color.set(1, 1, 1);
    }

    Fish(const Fish &f) {
        position = f.position;
        size = f.size;
        direction = f.direction;
        width = f.width;
        height = f.height;
        color.set(1, 1, 1);
    }

    void set(Point &position, float size, int direction) {
        this->position.set(position);
        this->size = size;
        this->direction = direction;
    }

    void set(Point &position, float size, int direction, float width, float height) {
        this->position.set(position);
        this->size = size;
        this->direction = direction;
        this->width = width;
        this->height = height;
    }

    void set(const Fish &f) {
        position = f.position;
        size = f.size;
        direction = f.direction;
        width = f.width;
        height = f.height;
    }

    void move(float displacement) { position.x += displacement; }

    void draw() {
        float w = width;
        float h = height;
        glPushMatrix();
        glTranslatef(position.x, position.y + h / 2 * size, 0);
        if (direction != 0)
            glScalef(size, size, 1);
        else
            glScalef(-size, size, 1);
        glColor4f(color.r, color.g, color.b, color.a);
        glBegin(GL_TRIANGLES);
        // tail
        glVertex2f(-w / 4, 0);
        glVertex2f(-w / 2, h / 4);
        glVertex2f(-w / 2, -h / 4);
        // body
        glVertex2f(-w / 4, 0);
        glVertex2f(0, h / 4);
        glVertex2f(0, -h / 4);
        // head
        glVertex2f(w / 2, 0);
        glVertex2f(0, h / 2);
        glVertex2f(0, -h / 2);
        glEnd();
        glPopMatrix();
    }
};

class Food {
  public:
    Point position;
    float size;
    int type;
    float width;
    float height;
    Color color;

    Food() {}

    Food(float x, float y, float size, int type) {
        this->position.set(x, y);
        this->size = size;
        this->type = type;
        this->width = 1;
        this->height = 1;
        this->color.set(1, 1, 1);
    }

    Food(float x, float y, float size, int type, const Color &c) {
        this->position.set(x, y);
        this->size = size;
        this->type = type;
        this->width = 1;
        this->height = 1;
        this->color.set(c.r, c.g, c.b);
    }

    Food(float x, float y, float size, int type, float width, float height) {
        this->position.set(x, y);
        this->size = size;
        this->type = type;
        this->width = width;
        this->height = height;
        this->color.set(1, 1, 1);
    }

    Food(const Point &position, float size, int type, float width, float height) {
        this->position.set(position);
        this->size = size;
        this->type = type;
        this->width = width;
        this->height = height;
        this->color.set(1, 1, 1);
    }

    Food(const Food &f) {
        position = f.position;
        size = f.size;
        type = f.type;
        width = f.width;
        height = f.height;
        color.set(f.color);
    }

    void set(const Point &position, float size, int type, float width, float height) {
        this->position.set(position);
        this->size = size;
        this->type = type;
        this->width = width;
        this->height = height;
    }

    void set(const Food &f) {
        position = f.position;
        size = f.size;
        type = f.type;
        width = f.width;
        height = f.height;
    }

    void draw() {
        float w = width;
        float h = height;
        if (type == 1) {
            glColor4f(color.r, color.g, color.b, color.a);
            glPushMatrix();
            glTranslatef(position.x, position.y, 0);
            glScalef(size, size, 1);
            glBegin(GL_POLYGON);
            glVertex2f(-w / 2, -h / 2);
            glVertex2f(-w / 2, h / 2);
            glVertex2f(w / 2, h / 2);
            glVertex2f(w / 2, -h / 2);
            glEnd();
            glPopMatrix();
        } else {
            glColor4f(color.r, color.g, color.b, color.a);
            glPushMatrix();
            glTranslatef(position.x, position.y, 0);
            glScalef(size, size, 1);
            float pi = 4 * atan(1);
            int n = 100;
            float t = 2 * pi / (n - 1);
            glBegin(GL_POLYGON);
            for (int i = 0; i < n; ++i)
                glVertex2f(w / 2 * cos(i * t), h / 2 * sin(i * t));
            glEnd();
            glPopMatrix();
        }
    }
};

#endif
