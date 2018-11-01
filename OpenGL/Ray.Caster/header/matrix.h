#ifndef MATRIX_H
#define MATRIX_H

#include <cmath>
#include <cstdio>

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
    Point(float, float, float, float);
    void set(float, float, float);
    void set(float, float, float, float);
    void set(const Point &);
    float distFromOrigin();
    const Vector &operator-(const Point &) const;
    const Point &operator+(const Vector &) const;
    const Point &operator-(const Vector &) const;
    void operator=(const Point &);
    void Print();
};

// 3D vectors
class Vector {
public:
    // float v[4];
    float x, y, z, h;
    Vector();
    Vector(const Vector &);
    Vector(float, float, float);
    Vector(float, float, float, float);
    void set(const Vector &);
    void set(float, float, float);
    void set(float, float, float, float);
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
    void operator=(const Vector &);
    void Print();
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
    const Matrix &Inverse();
    const Point &operator*(const Point &)const; // 3DPoint = matrix * 3Dpoint;
    const Vector &
    operator*(const Vector &)const; // 3Dvector = matrix * 3Dvector;
    const Matrix &operator*(const Matrix &)const; // matrix = matrix * matrix;
    const Matrix &operator*(float)const;          // matrix = matrix * float;
    void operator=(const Matrix &);               // set matrix from matrix
    void operator=(float *);                      // set matrix from array
    void SetToIdentity(); // set matrix to identity matrix
    void Print();
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

Point::Point(float i, float j, float k)
{
    x = i;
    y = j;
    z = k;
    h = 1.0;
}

Point::Point(float i, float j, float k, float l)
{
    x = i;
    y = j;
    z = k;
    h = l;
}

Point::Point()
{
    x = 0.0;
    y = 0.0;
    z = 0.0;
    h = 1.0;
}

Point::Point(const Point &p)
{
    x = p.x;
    y = p.y;
    z = p.z;
    h = p.h;
}

void Point::Print()
{
    printf("[%f, %f, %f, %f]\n\n", x, y, z, h);
}

void Point::set(float i, float j, float k)
{
    x = i;
    y = j;
    z = k;
    h = 1.0;
}

void Point::set(float i, float j, float k, float l)
{
    x = i;
    y = j;
    z = k;
    h = l;
}

void Point::set(const Point &p) { set(p.x, p.y, p.z); }

float Point::distFromOrigin()
{
    return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

void Vector::Print() {
    printf("[%f, %f, %f, %f]\n\n", x, y, z, h);
}
const Vector &Point::operator-(const Point &p) const
{
    Vector *r = new Vector(x - p.x, y - p.y, z - p.z);
    return *r;
}

const Point &Point::operator+(const Vector &v) const
{
    Point *r = new Point(x + v.x, y + v.y, z + v.z);
    return *r;
}

const Point &Point::operator-(const Vector &v) const
{
    Point *r = new Point(x - v.x, y - v.y, z - v.z);
    return *r;
}


void Point::operator=(const Point &p)
{
    x = p.x;
    y = p.y;
    z = p.z;
    h = p.h;
}

Vector::Vector(float i, float j, float k)
{
    x = i;
    y = j;
    z = k;
    h = 0.0;
}

Vector::Vector(float i, float j, float k, float l)
{
    x = i;
    y = j;
    z = k;
    h = l;
}

Vector::Vector() { x = y = z = h = 0.0; }

Vector::Vector(const Vector &v)
{
    x = v.x;
    y = v.y;
    z = v.z;
    h = 0.0;
}

void Vector::set(float i, float j, float k)
{
    x = i;
    y = j;
    z = k;
    h = 0.0;
}

void Vector::set(float i, float j, float k, float l)
{
    x = i;
    y = j;
    z = k;
    h = l;
}

void Vector::set(const Vector &v) { this->set(v.x, v.y, v.z); }

float Vector::dot(Vector &v) { return x * v.x + y * v.y + z * v.z; }

float Vector::dot(Point &p) { return x * p.x + y * p.y + z * p.z; }

Vector Vector::cross(Vector &v)
{
    Vector r;
    r.x = y * v.z - z * v.y;
    r.y = z * v.x - x * v.z;
    r.z = x * v.y - y * v.x;
    return r;
}

Vector Vector::cross(Point &p)
{
    Vector r;
    r.x = y * p.z - z * p.y;
    r.y = z * p.x - x * p.z;
    r.z = x * p.y - y * p.x;
    return r;
}

Vector Vector::newell(Point pnt[3])
{
    Vector r;
    r.x = 0;
    r.y = 0;
    r.z = 0;
    int next = 0;
    for (int i = 0; i < 3; i++) {
        next = i + 1;
        if (next > 2) {
            next = 0;
        }
        r.x += (pnt[i].y - pnt[next].y) * (pnt[i].z + pnt[next].z);
        r.y += (pnt[i].z - pnt[next].z) * (pnt[i].x + pnt[next].x);
        r.z += (pnt[i].x - pnt[next].x) * (pnt[i].y + pnt[next].y);
    }
    return r;
}

void Vector::normalize()
{
    float d;
    d = magnitude();
    x /= d;
    y /= d;
    z /= d;
}

float Vector::magnitude() { return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2)); }

const Vector &Vector::operator+(const Vector &v) const
{
    Vector *r = new Vector(x + v.x, y + v.y, z + v.z);
    return *r;
}

const Vector &Vector::operator-(const Vector &v) const
{
    Vector *r = new Vector(x - v.x, y - v.y, z - v.z);
    return *r;
}

const Vector &Vector::operator*(float s) const
{
    Vector *r = new Vector(x * s, y * s, z * s);
    return *r;
}

void Vector::operator=(const Vector &v)
{
    x = v.x;
    y = v.y;
    z = v.z;
    h = v.h;
}

Matrix::Matrix() { SetToIdentity(); }

void Matrix::SetToIdentity()
{
    m[0] = 1;
    m[4] = 0;
    m[8] = 0;
    m[12] = 0;
    m[1] = 0;
    m[5] = 1;
    m[9] = 0;
    m[13] = 0;
    m[2] = 0;
    m[6] = 0;
    m[10] = 1;
    m[14] = 0;
    m[3] = 0;
    m[7] = 0;
    m[11] = 0;
    m[15] = 1;
}

const Point &Matrix::operator*(const Point &p) const
{
    Point *r = new Point();
    r->x = p.x * m[0] + p.y * m[4] + p.z * m[8] + p.h * m[12];
    r->y = p.x * m[1] + p.y * m[5] + p.z * m[9] + p.h * m[13];
    r->z = p.x * m[2] + p.y * m[6] + p.z * m[10] + p.h * m[14];
    r->h = p.x * m[3] + p.y * m[7] + p.z * m[11] + p.h * m[15];
    return *r;
}

const Vector &Matrix::operator*(const Vector &v) const
{
    Vector *r = new Vector();
    r->x = v.x * m[0] + v.y * m[4] + v.z * m[8] + v.h * m[12];
    r->y = v.x * m[1] + v.y * m[5] + v.z * m[9] + v.h * m[13];
    r->z = v.x * m[2] + v.y * m[6] + v.z * m[10] + v.h * m[14];
    r->h = v.x * m[3] + v.y * m[7] + v.z * m[11] + v.h * m[15];
    return *r;
}

const Matrix &Matrix::operator*(const Matrix &mat) const
{
    Matrix *r = new Matrix();
    r->m[0] =
        m[0] * mat.m[0] + m[4] * mat.m[1] + m[8] * mat.m[2] + m[12] * mat.m[3];
    r->m[1] =
        m[1] * mat.m[0] + m[5] * mat.m[1] + m[9] * mat.m[2] + m[13] * mat.m[3];
    r->m[2] =
        m[2] * mat.m[0] + m[6] * mat.m[1] + m[10] * mat.m[2] + m[14] * mat.m[3];
    r->m[3] =
        m[3] * mat.m[0] + m[7] * mat.m[1] + m[11] * mat.m[2] + m[15] * mat.m[3];
    r->m[4] =
        m[0] * mat.m[4] + m[4] * mat.m[5] + m[8] * mat.m[6] + m[12] * mat.m[7];
    r->m[5] =
        m[1] * mat.m[4] + m[5] * mat.m[5] + m[9] * mat.m[6] + m[13] * mat.m[7];
    r->m[6] =
        m[2] * mat.m[4] + m[6] * mat.m[5] + m[10] * mat.m[6] + m[14] * mat.m[7];
    r->m[7] =
        m[3] * mat.m[4] + m[7] * mat.m[5] + m[11] * mat.m[6] + m[15] * mat.m[7];
    r->m[8] = m[0] * mat.m[8] + m[4] * mat.m[9] + m[8] * mat.m[10] +
              m[12] * mat.m[11];
    r->m[9] = m[1] * mat.m[8] + m[5] * mat.m[9] + m[9] * mat.m[10] +
              m[13] * mat.m[11];
    r->m[10] = m[2] * mat.m[8] + m[6] * mat.m[9] + m[10] * mat.m[10] +
               m[14] * mat.m[11];
    r->m[11] = m[3] * mat.m[8] + m[7] * mat.m[9] + m[11] * mat.m[10] +
               m[15] * mat.m[11];
    r->m[12] = m[0] * mat.m[12] + m[4] * mat.m[13] + m[8] * mat.m[14] +
               m[12] * mat.m[15];
    r->m[13] = m[1] * mat.m[12] + m[5] * mat.m[13] + m[9] * mat.m[14] +
               m[13] * mat.m[15];
    r->m[14] = m[2] * mat.m[12] + m[6] * mat.m[13] + m[10] * mat.m[14] +
               m[14] * mat.m[15];
    r->m[15] = m[3] * mat.m[12] + m[7] * mat.m[13] + m[11] * mat.m[14] +
               m[15] * mat.m[15];
    return *r;
}

const Matrix &Matrix::operator*(float s) const
{
    Matrix *mat = new Matrix();
    int i;
    for (i = 0; i < 16; ++i) {
        mat->m[i] = m[i] * s;
    }
    return *mat;
}

void Matrix::operator=(const Matrix &mat)
{
    m[0] = mat.m[0];
    m[1] = mat.m[1];
    m[2] = mat.m[2];
    m[3] = mat.m[3];
    m[4] = mat.m[4];
    m[5] = mat.m[5];
    m[6] = mat.m[6];
    m[7] = mat.m[7];
    m[8] = mat.m[8];
    m[9] = mat.m[9];
    m[10] = mat.m[10];
    m[11] = mat.m[11];
    m[12] = mat.m[12];
    m[13] = mat.m[13];
    m[14] = mat.m[14];
    m[15] = mat.m[15];
}

void Matrix::operator=(float *mat)
{
    m[0] = mat[0];
    m[1] = mat[1];
    m[2] = mat[2];
    m[3] = mat[3];
    m[4] = mat[4];
    m[5] = mat[5];
    m[6] = mat[6];
    m[7] = mat[7];
    m[8] = mat[8];
    m[9] = mat[9];
    m[10] = mat[10];
    m[11] = mat[11];
    m[12] = mat[12];
    m[13] = mat[13];
    m[14] = mat[14];
    m[15] = mat[15];
}

void Transform::Translate(float x, float y)
{
    Matrix mat;
    mat.m[9] = y;
    mat.m[8] = x;
    matrix = matrix * mat;
}

void Transform::Translate(float x, float y, float z)
{
    Matrix mat;
    mat.m[14] = z;
    mat.m[13] = y;
    mat.m[12] = x;
    matrix = matrix * mat;
}

void Transform::Rotate(float degrees)
{
    Matrix mat;
    float c, s;
    static float const pi = 4 * atan(1.0);
    degrees = degrees * pi / 180;
    c = cos(degrees);
    s = sin(degrees);

    mat.m[0] = c;
    mat.m[1] = s;
    mat.m[4] = -1 * s;
    mat.m[5] = c;

    matrix = matrix * mat;
}

void Transform::Rotate(float degrees, float vx, float vy, float vz)
{
    Matrix mat;
    float x, y, z, ic, c, s, d;
    static float const pi = 4 * atan(1.0);

    vx = pow(vx, 2.0);
    vy = pow(vy, 2.0);
    vz = pow(vz, 2.0);
    d = vx + vy + vz;
    if (d > 0) {
        vx /= d;
        vy /= d;
        vz /= d;
        x = sqrt(vx);
        y = sqrt(vy);
        z = sqrt(vz);

        degrees = degrees * pi / 180;
        c = cos(degrees);
        s = sin(degrees);
        ic = 1 - c;

        mat.m[0] = vx + (1 - vx) * c;
        mat.m[1] = x * y * ic + z * s;
        mat.m[2] = x * z * ic - y * s;
        mat.m[3] = 0;
        mat.m[4] = x * y * ic - z * s;
        mat.m[5] = vy + (1 - vy) * c;
        mat.m[6] = y * z * ic + x * s;
        mat.m[7] = 0;
        mat.m[8] = x * z * ic + y * s;
        mat.m[9] = y * z * ic - x * s;
        mat.m[10] = vz + (1 - vz) * c;
        mat.m[11] = 0;
        mat.m[12] = 0;
        mat.m[13] = 0;
        mat.m[14] = 0;
        mat.m[15] = 1;

        matrix = matrix * mat;
    }
}

void Transform::Scale(float x, float y)
{
    Matrix mat;
    mat.m[0] = x;
    mat.m[5] = y;
    matrix = matrix * mat;
}

void Transform::Scale(float x, float y, float z)
{
    Matrix mat;
    mat.m[0] = x;
    mat.m[5] = y;
    mat.m[10] = z;
    matrix = matrix * mat;
}

void Transform::Shear(float x, float y)
{
    Matrix mat;
    mat.m[4] = x;
    mat.m[1] = y;
    matrix = matrix * mat;
}

void Transform::Shear(float x, float y, float z)
{
    Matrix mat;
    mat.m[1] = y;
    mat.m[2] = x;
    mat.m[4] = x;
    mat.m[6] = y;
    mat.m[8] = z;
    mat.m[9] = z;
    matrix = matrix * mat;
}

const Matrix &Matrix::Inverse()
{
    Matrix mat;
    mat.m[0] = m[9] * m[14] * m[11] - m[13] * m[10] * m[11] +
               m[13] * m[6] * m[11] - m[5] * m[14] * m[11] -
               m[9] * m[6] * m[15] + m[5] * m[10] * m[15];
    mat.m[4] = m[12] * m[10] * m[11] - m[8] * m[14] * m[11] -
               m[12] * m[6] * m[11] + m[4] * m[14] * m[11] +
               m[8] * m[6] * m[15] - m[4] * m[10] * m[15];
    mat.m[8] = m[8] * m[13] * m[11] - m[12] * m[9] * m[11] +
               m[12] * m[5] * m[11] - m[4] * m[13] * m[11] -
               m[8] * m[5] * m[15] + m[4] * m[9] * m[15];
    mat.m[12] = m[12] * m[9] * m[6] - m[8] * m[13] * m[6] -
                m[12] * m[5] * m[10] + m[4] * m[13] * m[10] +
                m[8] * m[5] * m[14] - m[4] * m[9] * m[14];
    mat.m[1] = m[13] * m[10] * m[3] - m[9] * m[14] * m[3] -
               m[13] * m[2] * m[11] + m[1] * m[14] * m[11] +
               m[9] * m[2] * m[15] - m[1] * m[10] * m[15];
    mat.m[5] = m[8] * m[14] * m[3] - m[12] * m[10] * m[3] +
               m[12] * m[2] * m[11] - m[0] * m[14] * m[11] -
               m[8] * m[2] * m[15] + m[0] * m[10] * m[15];
    mat.m[9] = m[12] * m[9] * m[3] - m[8] * m[13] * m[3] -
               m[12] * m[1] * m[11] + m[0] * m[13] * m[11] +
               m[8] * m[1] * m[15] - m[0] * m[9] * m[15];
    mat.m[13] = m[8] * m[13] * m[2] - m[12] * m[9] * m[2] +
                m[12] * m[1] * m[10] - m[0] * m[13] * m[10] -
                m[8] * m[1] * m[14] + m[0] * m[9] * m[14];
    mat.m[2] = m[5] * m[14] * m[3] - m[13] * m[6] * m[3] +
               m[13] * m[2] * m[11] - m[1] * m[14] * m[11] -
               m[5] * m[2] * m[15] + m[1] * m[6] * m[15];
    mat.m[6] = m[12] * m[6] * m[3] - m[4] * m[14] * m[3] -
               m[12] * m[2] * m[11] + m[0] * m[14] * m[11] +
               m[4] * m[2] * m[15] - m[0] * m[6] * m[15];
    mat.m[10] = m[4] * m[13] * m[3] - m[12] * m[5] * m[3] +
                m[12] * m[1] * m[11] - m[0] * m[13] * m[11] -
                m[4] * m[1] * m[15] + m[0] * m[5] * m[15];
    mat.m[14] = m[12] * m[5] * m[2] - m[4] * m[13] * m[2] -
                m[12] * m[1] * m[6] + m[0] * m[13] * m[6] +
                m[4] * m[1] * m[14] - m[0] * m[5] * m[14];
    mat.m[3] = m[9] * m[6] * m[3] - m[5] * m[10] * m[3] - m[9] * m[2] * m[11] +
               m[1] * m[10] * m[11] + m[5] * m[2] * m[11] - m[1] * m[6] * m[11];
    mat.m[7] = m[4] * m[10] * m[3] - m[8] * m[6] * m[3] + m[8] * m[2] * m[11] -
               m[0] * m[10] * m[11] - m[4] * m[2] * m[11] + m[0] * m[6] * m[11];
    mat.m[11] = m[8] * m[5] * m[3] - m[4] * m[9] * m[3] - m[8] * m[1] * m[11] +
                m[0] * m[9] * m[11] + m[4] * m[1] * m[11] - m[0] * m[5] * m[11];
    mat.m[15] = m[4] * m[9] * m[2] - m[8] * m[5] * m[2] + m[8] * m[1] * m[6] -
                m[0] * m[9] * m[6] - m[4] * m[1] * m[10] + m[0] * m[5] * m[10];
    return mat * (1 / Determinant());
}

float Matrix::Determinant()
{
    return m[12] * m[9] * m[6] * m[3] - m[8] * m[13] * m[6] * m[3] -
           m[12] * m[5] * m[10] * m[3] + m[4] * m[13] * m[10] * m[3] +
           m[8] * m[5] * m[14] * m[3] - m[4] * m[9] * m[14] * m[3] -
           m[12] * m[9] * m[2] * m[11] + m[8] * m[13] * m[2] * m[11] +
           m[12] * m[1] * m[10] * m[11] - m[0] * m[13] * m[10] * m[11] -
           m[8] * m[1] * m[14] * m[11] + m[0] * m[9] * m[14] * m[11] +
           m[12] * m[5] * m[2] * m[11] - m[4] * m[13] * m[2] * m[11] -
           m[12] * m[1] * m[6] * m[11] + m[0] * m[13] * m[6] * m[11] +
           m[4] * m[1] * m[14] * m[11] - m[0] * m[5] * m[14] * m[11] -
           m[8] * m[5] * m[2] * m[15] + m[4] * m[9] * m[2] * m[15] +
           m[8] * m[1] * m[6] * m[15] - m[0] * m[9] * m[6] * m[15] -
           m[4] * m[1] * m[10] * m[15] + m[0] * m[5] * m[10] * m[15];
}

void Matrix::Print()
{
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            printf("%f ", m[j * 4 + i]);
        }
        printf("\n");
    }
    printf("\n");
}

#endif
