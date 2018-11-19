// color.h
// Implementation for Color Class
// COSC 5450 Project 3a/3b/3c
// Libao Jin
// Updated date: 11/15/2018

#ifndef COLOR_H
#define COLOR_H

#include <cstdio>

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

    const Color &operator+(const Color &c) const
    {
        float nr = r + c.r > 1 ? 1 : r + c.r;
        float ng = g + c.g > 1 ? 1 : g + c.g;
        float nb = b + c.b > 1 ? 1 : b + c.b;
        Color *ret = new Color(nr, ng, nb);
        return *ret;
    }

    const Color &operator*(const Color &c) const
    {
        float nr = r * c.r > 1 ? 1 : r * c.r;
        float ng = g * c.g > 1 ? 1 : g * c.g;
        float nb = b * c.b > 1 ? 1 : b * c.b;
        Color *ret = new Color(nr, ng, nb);
        return *ret;
    }

    const Color &operator*(float c) const
    {
        float nr = r * c > 1 ? 1 : r * c;
        float ng = g * c > 1 ? 1 : g * c;
        float nb = b * c > 1 ? 1 : b * c;
        Color *ret = new Color(nr, ng, nb);
        return *ret;
    }
    void operator=(const Color &c)
    {
        r = c.r;
        g = c.g;
        b = c.b;
        a = c.a;
    }

    void operator+=(const Color &c)
    {
        r = r + c.r > 1 ? 1 : r + c.r;
        g = g + c.g > 1 ? 1 : g + c.g;
        b = b + c.b > 1 ? 1 : b + c.b;
        a = c.a;
    }

    void operator*=(const Color &c)
    {
        r = r * c.r > 1 ? 1 : r * c.r;
        g = g * c.g > 1 ? 1 : g * c.g;
        b = b * c.b > 1 ? 1 : b * c.b;
        a = a * c.a > 1 ? 1 : a * c.a;
    }

    bool operator!=(const Color &c)
    {
        return !(r == c.r && g == c.g && b == c.b);
    }

    bool operator==(const Color &c)
    {
        return (r == c.r && g == c.g && b == c.b);
    }

    void Print()
    {
        printf("[r g b a] = [%.2f %.2f %.2f %.2f]\n", r, g, b, a);
    }
};

#endif
