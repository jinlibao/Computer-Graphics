#ifndef OBJECT_H
#define OBJECT_H

#include "color.h"
#include "matrix.h"

using namespace std;

class Object {
public:
    string type;
    float radius;
    float length;
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

    void setTransform(float radius, float length, Point center)
    {
        transform_matrix.Translate(center.x, center.y, center.z);
        transform_matrix.Scale(radius, length, radius);
        inverse_transform_matrix = transform_matrix.matrix.Inverse();
    }

    Object(const Object &o)
    {
        type = o.type;
        radius = o.radius;
        center.set(o.center);
        color.set(o.color);
        transform_matrix.matrix = o.transform_matrix.matrix;
        inverse_transform_matrix = o.inverse_transform_matrix;
    }

    Object(string type, float radius, Point &center, Color &color)
    {
        this->type = type;
        this->radius = radius;
        this->center.set(center);
        this->color.set(color);
        setTransform(this->radius, this->center);
    }

    Object(string type, float radius, float length, Point &center, Color &color)
    {
        this->type = type;
        this->radius = radius;
        this->length = length;
        this->center.set(center);
        this->color.set(color);
        setTransform(this->radius, this->length, this->center);
    }

    Object(string type, float radius, float x, float y, float z, float r, float g, float b)
    {
        this->type = type;
        this->radius = radius;
        center.set(x, y, z);
        color.set(r, g, b);
        setTransform(radius, center);
    }

    Object(string type, float radius, float length, float x, float y, float z, float r, float g, float b)
    {
        this->type = type;
        this->radius = radius;
        this->length = length;
        center.set(x, y, z);
        color.set(r, g, b);
        setTransform(radius, length, center);
    }

    void set(string type, float radius, Point &center, Color &color)
    {
        this->type = type;
        this->radius = radius;
        this->center.set(center);
        this->color.set(color);
        setTransform(this->radius, this->center);
    }

    void set(string type, float radius, float length, Point &center, Color &color)
    {
        this->type = type;
        this->radius = radius;
        this->length = length;
        this->center.set(center);
        this->color.set(color);
        setTransform(this->radius, this->length, this->center);
    }

    void set(string type, float radius, float x, float y, float z, float r, float g, float b)
    {
        this->type = type;
        this->radius = radius;
        center.set(x, y, z);
        color.set(r, g, b);
        setTransform(radius, center);
    }

    void set(string type, float radius, float length, float x, float y, float z, float r, float g, float b)
    {
        this->type = type;
        this->radius = radius;
        this->length = length;
        center.set(x, y, z);
        color.set(r, g, b);
        setTransform(radius, length, center);
    }
};

#endif
