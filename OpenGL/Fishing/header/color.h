// color.h
// Implementation for Color class
// COSC 5450 Project 4
// Libao Jin <ljin1@uwyo.edu>
// Updated date: 11/30/2018

#ifndef COLOR_H
#define COLOR_H

#include <cstdio>

class Color {
public:
    float r;
    float g;
    float b;
    float a;

    Color() {}

    Color(float r, float g, float b, float a)
    {
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
    }

    Color(float r, float g, float b)
    {
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = 1;
    }

    Color(const Color &c)
    {
        r = c.r;
        g = c.g;
        b = c.b;
        a = c.a;
    }

    void set(float r, float g, float b, float a)
    {
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
    }

    void set(float r, float g, float b)
    {
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = 1;
    }

    void set(const Color &c)
    {
        r = c.r;
        g = c.g;
        b = c.b;
        a = c.a;
    }

    void print() { printf("[%.4f, %.4f, %.4f, %.4f]\n", r, g, b, a); }
};

#endif
