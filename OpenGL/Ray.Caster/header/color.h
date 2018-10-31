// color.h
// Implementation for Coloc Class
// COSC 5450 Project 3a
// Libao Jin
// 10/29/2018

#ifndef COLOR_H
#define COLOR_H

class Color {
public:
    float r;
    float g;
    float b;
    float a;

    Color()
    {
        r = 0.0;
        g = 0.0;
        b = 0.0;
        a = 1.0;
    }

    Color(float r, float g, float b)
    {
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = 1.0;
    }

    Color(float r, float g, float b, float a)
    {
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
    }

    Color(const Color &c)
    {
        r = c.r;
        g = c.g;
        b = c.b;
        a = c.a;
    }

    void set(const Color &c)
    {
        r = c.r;
        g = c.g;
        b = c.b;
        a = c.a;
    }

    void set(float r, float g, float b)
    {
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = 1.0;
    }

    void set(float r, float g, float b, float a)
    {
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
    }
};

#endif
