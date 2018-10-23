#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <sstream>
#include <string>
#include <math.h>

class Point2D;
class Vector2D;
class Matrix2D;
class Point;
class Vector;
class Matrix;

float const e = 2.718281828f;
float const pi = 3.141592653f;

//2D points
class Point2D {

public:
    //float p[3];
    float x;
    float y;
    float h;
    Point2D();
    Point2D(float, float);
};

//2D vectors
class Vector2D {

public:
    //float v[3];
    float x;
    float y;
    float h;
    Vector2D();
    Vector2D(float, float);
};

//3D points
class Point {

public:
    //float p[4];
    float x;
    float y;
    float z;
    float h;
    Point();
    Point(Point&);
    Point(float, float, float);
    void set(Point&);
    void set(float, float, float);

    Vector operator-(Point&);
    Point operator+(Vector&);

    void Print();
};

//3D vectors
class Vector {

public:
    //float v[4];
    float x;
    float y;
    float z;
    float h;
    Vector();
    Vector(Vector&);
    Vector(float, float, float);
    void set(Vector&);
    void set(float, float, float);
    float dot(Vector&);
    float dot(Point&);
    Vector cross(Vector&);
    Vector cross(Point&);
    void normalize();
    float magnitude();

    Vector operator+(Vector&);
    Vector operator-(Vector&);
    Vector operator*(float);
    Vector newell(Point[3]);
    void Print();
};

//Matrices
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

    void Print(int);
    void Print();

    Point2D operator*(Point2D&);// 2DPoint = matrix * Dpoint;
    Vector2D operator*(Vector2D&);// 2Dvector = matrix * 2Dvector;

    Point operator*(Point&);// 3DPoint = matrix * 3Dpoint;
    Vector operator*(Vector&);// 3Dvector = matrix * 3Dvector;
    Matrix operator*(Matrix&);// matrix = matrix * matrix;
    Matrix operator*(float);//matrix = matrix * float;

    void operator=(Matrix&);//set matrix from matrix
    void operator=(float*);//set matrix from array

    void SetToIdentity();//set matrix to identity matrix

    void Translate(float, float);//2D translate
    void Translate(float, float, float);//3Dtranslate

    void Rotate(float);//rotate around z axis
    void Rotate(float, float, float, float);//3D rotate

    void Scale(float, float);//2D scale
    void Scale(float, float, float);//3D scale

    void Shear(float, float);//2D Shear
    void Shear(float, float, float);//3D shear

};

//Transformations
class Transform {

public:
    Matrix matrix;
    void Translate(float, float);//2D translate
    void Translate(float, float, float);//3Dtranslate

    void Rotate(float);//rotate around z axis
    void Rotate(float, float, float, float);//3D rotate

    void Scale(float, float);//2D scale
    void Scale(float, float, float);//3D scale

    void Shear(float, float);//2D Shear
    void Shear(float, float, float);//3D shear
};

#endif
