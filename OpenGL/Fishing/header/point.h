// matrix.h
// Implementation for Vector class
// COSC 5450 Project 4
// Libao Jin <ljin1@uwyo.edu>
// Updated date: 11/30/2018

#ifndef MATRIX_H
#define MATRIX_H

#include <cstdio>

class Point {
  public:
    float x;
    float y;
    float z;
    float h;

    Point() {
        this->x = 0;
        this->y = 0;
        this->z = 0;
        this->h = 1;
    }

    Point(float x, float y) {
        this->x = x;
        this->y = y;
        this->z = 0;
        this->h = 1;
    }

    Point(float x, float y, float z) {
        this->x = x;
        this->y = y;
        this->z = z;
        this->h = 1;
    }

    Point(const Point &p) {
        x = p.x;
        y = p.y;
        z = p.z;
        h = p.h;
    }

    void set(float x, float y) {
        this->x = x;
        this->y = y;
        this->z = 0;
        this->h = 1;
    }

    void set(float x, float y, float z) {
        this->x = x;
        this->y = y;
        this->z = z;
        this->h = 1;
    }

    void set(const Point &p) {
        x = p.x;
        y = p.y;
        z = p.z;
        h = p.h;
    }

    void print() { printf("[%.4f, %.4f, %.4f, %.4f]\n", x, y, z, h); }
};

#endif
