// fish.h
// Implementation for Fish and Food class
// COSC 5450 Project 4
// Libao Jin <ljin1@uwyo.edu>
// Updated date: 11/30/2018

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

#include "point.h"

using namespace std;

class Food;

class Fish {
public:
    Point position;
    float size;
    int direction;

    Fish() {}

    Fish(float x, float y, float size, int direction)
    {
        this->position.set(x, y);
        this->size = size;
        this->direction = direction;
    }

    Fish(Point &position, float size, int direction)
    {
        this->position.set(position);
        this->size = size;
        this->direction = direction;
    }

    Fish(const Fish &f)
    {
        position = f.position;
        size = f.size;
        direction = f.direction;
    }

    void set(Point &position, float size, int direction)
    {
        this->position.set(position);
        this->size = size;
        this->direction = direction;
    }

    void set(const Fish &f)
    {
        position = f.position;
        size = f.size;
        direction = f.direction;
    }

    void move(float displacement) { position.x += displacement; }

    void draw()
    {
        if (direction != 0) {
            glPushMatrix();
            glTranslatef(position.x, position.y, 0);
            glScalef(size, size, 1);
            glBegin(GL_TRIANGLES);
            glVertex2f(0, 0);
            glVertex2f(0, 2);
            glVertex2f(1, 1);
            glEnd();
            glBegin(GL_POLYGON);
            glVertex2f(1, 1);
            glVertex2f(2, 2);
            glVertex2f(3, 1);
            glVertex2f(2, 0);
            glEnd();
            glPopMatrix();
        }
        else {
            glPushMatrix();
            glTranslatef(position.x, position.y, 0);
            glScalef(size, size, 1);
            glBegin(GL_TRIANGLES);
            glVertex2f(2, 1);
            glVertex2f(3, 2);
            glVertex2f(3, 0);
            glEnd();
            glBegin(GL_POLYGON);
            glVertex2f(0, 1);
            glVertex2f(1, 2);
            glVertex2f(2, 1);
            glVertex2f(1, 0);
            glEnd();
            glPopMatrix();
        }
    }
};

class Food {
public:
    Point position;
    float size;

    Food() {}

    Food(float x, float y, float size)
    {
        this->position.set(x, y);
        this->size = size;
    }

    Food(const Point &position, float size)
    {
        this->position.set(position);
        this->size = size;
    }

    Food(const Food &f)
    {
        position = f.position;
        size = f.size;
    }

    void set(const Point &position, float size)
    {
        this->position.set(position);
        this->size = size;
    }

    void set(const Food &f)
    {
        position = f.position;
        size = f.size;
    }

    void draw()
    {
        glPushMatrix();
        glTranslatef(position.x, position.y, 0);
        glScalef(size, size, 1);
        glBegin(GL_POLYGON);
        glVertex2f(0, 0);
        glVertex2f(0, 1);
        glVertex2f(1, 1);
        glVertex2f(1, 0);
        glEnd();
        glPopMatrix();
    }
};

#endif
