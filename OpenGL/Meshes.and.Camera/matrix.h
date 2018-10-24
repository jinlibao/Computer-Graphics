#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <math.h>
#include <sstream>
#include <string>

class Point;
class Vector;
class Matrix;

float const e = exp(1.0);
float const pi = 4 * atan(1.0f);

// 3D points
class Point {
public:
    // float p[4];
    float x, y, z, h;
    Point();
    Point(const Point &);
    Point(float, float, float);
    void set(float, float, float);
    void set(const Point &);
    const Vector &operator-(const Point &) const;
    const Point &operator+(const Vector &) const;
    const Point &operator-(const Vector &) const;
};

// 3D vectors
class Vector {
public:
    // float v[4];
    float x, y, z, h;
    Vector();
    Vector(const Vector &);
    Vector(float, float, float);
    void set(const Vector &);
    void set(float, float, float);
    float dot(Vector &);
    float dot(Point &);
    Vector cross(Vector &);
    Vector cross(Point &);
    Vector newell(Point[3]);
    void normalize();
    float magnitude();
    const Vector &operator+(const Vector &) const;
    const Vector &operator-(const Vector &) const;
    const Vector &operator*(float)const;
};

// Matrices
class Matrix {
public:
    /*
       matrix array representation:
       [0 4 8  12]
       [1 5 9  13]
       [2 6 10 14]
       [3 7 11 15]
       */
    float m[16];
    Matrix();
    float Determinant();
    Matrix Inverse();
    const Point &operator*(const Point &)const; // 3DPoint = matrix * 3Dpoint;
    const Vector &
    operator*(const Vector &)const; // 3Dvector = matrix * 3Dvector;
    const Matrix &operator*(const Matrix &)const; // matrix = matrix * matrix;
    const Matrix &operator*(float)const;          // matrix = matrix * float;
    void operator=(const Matrix &);               // set matrix from matrix
    void operator=(float *);                      // set matrix from array
    void SetToIdentity();                    // set matrix to identity matrix
    void Translate(float, float);            // 2D translate
    void Translate(float, float, float);     // 3Dtranslate
    void Rotate(float);                      // rotate around z axis
    void Rotate(float, float, float, float); // 3D rotate
    void Scale(float, float);                // 2D scale
    void Scale(float, float, float);         // 3D scale
    void Shear(float, float);                // 2D Shear
    void Shear(float, float, float);         // 3D shear
};

// Transformations
class Transform {
public:
    Matrix matrix;
    void Translate(float, float);            // 2D translate
    void Translate(float, float, float);     // 3Dtranslate
    void Rotate(float);                      // rotate around z axis
    void Rotate(float, float, float, float); // 3D rotate
    void Scale(float, float);                // 2D scale
    void Scale(float, float, float);         // 3D scale
    void Shear(float, float);                // 2D Shear
    void Shear(float, float, float);         // 3D shear
};

#endif
