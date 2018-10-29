#ifndef SPHERE_H
#define SPHERE_H

#include "color.h"
#include "matrix.h"

class Sphere {
public:
    float radius;
    Point center;
    Color color;
    Transform transform_matrix;
    Matrix inverse_transform_matrix;

    void setTransform(float radius, Point center)
    {
        transform_matrix.Translate(center.x, center.y, center.z);
        transform_matrix.Scale(radius, radius, radius);
        inverse_transform_matrix = transform_matrix.matrix.Inverse();
    }

    Sphere(const Sphere &s)
    {
        radius = s.radius;
        center.set(s.center);
        color.set(s.color);
        transform_matrix.matrix = s.transform_matrix.matrix;
        inverse_transform_matrix = s.inverse_transform_matrix;
    }

    Sphere(float radius, Point &center, Color &color)
    {
        this->radius = radius;
        this->center.set(center);
        this->color.set(color);
        setTransform(this->radius, this->center);
    }

    Sphere(float radius, float x, float y, float z, float r, float g, float b)
    {
        this->radius = radius;
        center.set(x, y, z);
        color.set(r, g, b);
        setTransform(radius, center);
    }

    void set(float radius, Point &center, Color &color)
    {
        this->radius = radius;
        this->center.set(center);
        this->color.set(color);
        setTransform(this->radius, this->center);
    }

    void set(float radius, float x, float y, float z, float r, float g, float b)
    {
        this->radius = radius;
        center.set(x, y, z);
        color.set(r, g, b);
        setTransform(radius, center);
    }
};

#endif
