// object.h
// Implementation for Object Class
// Contains sphere and cylinder
// COSC 5450 Project 3a/3b/3c
// Libao Jin
// ljin1@uwyo.edu
// Updated: 10/29/2018

#ifndef OBJECT_H
#define OBJECT_H

#include "material.h"
#include "matrix.h"
#include <string>

using namespace std;

class Object {
public:
    string type;
    float radius;
    float length;
    Point center;
    Material material;
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
        material.set(o.material);
        transform_matrix.matrix = o.transform_matrix.matrix;
        inverse_transform_matrix = o.inverse_transform_matrix;
    }

    Object(string type, float radius, Point &center, Material &material)
    {
        this->type = type;
        this->radius = radius;
        this->center.set(center);
        this->material.set(material);
        setTransform(this->radius, this->center);
    }

    Object(string type, float radius, float length, Point &center, Material &material)
    {
        this->type = type;
        this->radius = radius;
        this->length = length;
        this->center.set(center);
        this->material.set(material);
        setTransform(this->radius, this->length, this->center);
    }

    Object(string type, float radius, float x, float y, float z, Material &m)
    {
        this->type = type;
        this->radius = radius;
        center.set(x, y, z);
        material.set(m);
        setTransform(radius, center);
    }

    Object(string type, float radius, float x, float y, float z, float r, float g, float b)
    {
        this->type = type;
        this->radius = radius;
        center.set(x, y, z);
        material.set(r, g, b);
        setTransform(radius, center);
    }

    Object(string type, float radius, float length, float x, float y, float z, float r, float g, float b)
    {
        this->type = type;
        this->radius = radius;
        this->length = length;
        center.set(x, y, z);
        material.set(r, g, b);
        setTransform(radius, length, center);
    }

    void set(string type, float radius, Point &center, Material &material)
    {
        this->type = type;
        this->radius = radius;
        this->center.set(center);
        this->material.set(material);
        setTransform(this->radius, this->center);
    }

    void set(string type, float radius, float length, Point &center, Material &material)
    {
        this->type = type;
        this->radius = radius;
        this->length = length;
        this->center.set(center);
        this->material.set(material);
        setTransform(this->radius, this->length, this->center);
    }

    void set(string type, float radius, float x, float y, float z, float r, float g, float b)
    {
        this->type = type;
        this->radius = radius;
        center.set(x, y, z);
        material.set(r, g, b);
        setTransform(radius, center);
    }

    void set(string type, float radius, float length, float x, float y, float z, float r, float g, float b)
    {
        this->type = type;
        this->radius = radius;
        this->length = length;
        center.set(x, y, z);
        material.set(r, g, b);
        setTransform(radius, length, center);
    }
};

#endif
