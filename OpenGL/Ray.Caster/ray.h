// ray.h
// Implementation for Ray and RayCast Class
// COSC 5450 Project 3(a)
// Libao Jin
// ljin1@uwyo.edu
// 10/29/2018

#ifndef RAY_H
#define RAY_H

#include "camera.h"
#include "color.h"
#include "matrix.h"
#include "sphere.h"
#include <algorithm>
#include <cfloat>
#include <vector>

#if defined __APPLE__ && !defined X11
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

using namespace std;

struct RGBpixel {
    unsigned char r, g, b;
};

class Ray {
public:
    Point start;
    Vector dir;

    Ray(){};
    Ray(const Point &start, const Vector &dir)
    {
        this->start.x = start.x;
        this->start.y = start.y;
        this->start.z = start.z;
        this->dir.x = dir.x;
        this->dir.y = dir.y;
        this->dir.z = dir.z;
    }

    void setStart(const Point &start)
    {
        this->start.x = start.x;
        this->start.y = start.y;
        this->start.z = start.z;
    }

    void setDir(const Vector &dir)
    {
        this->dir.x = dir.x;
        this->dir.y = dir.y;
        this->dir.z = dir.z;
    }

    void set(const Ray &ray)
    {
        setStart(ray.start);
        setDir(ray.dir);
    }
};

class RayCast {
public:
    Color backgroundColor;
    Ray ray;
    Ray inverseRay;
    int nRows;
    int nCols;
    int blockSize;
    RGBpixel **pixmap;
    float N, W, H;
    Vector u, v, n;

    RayCast(){};

    void set(Color &backgroundColor, int nCols, int nRows, int blockSize,
             Camera &camera)
    {
        this->backgroundColor.set(backgroundColor);
        this->nRows = nRows;
        this->nCols = nCols;
        this->blockSize = blockSize;
        this->N = camera.nearDist;
        this->W = camera.W;
        this->H = camera.H;
        this->u.set(camera.u);
        this->v.set(camera.v);
        this->n.set(camera.n);
        this->ray.start.set(camera.eye);
        pixmap = new RGBpixel *[nRows];
        pixmap[0] = new RGBpixel[nRows * nCols];
        for (int row = 1; row < nRows; row++)
            pixmap[row] = pixmap[row - 1] + nCols;
    }

    void set(Color &backgroundColor, int nCols, int nRows, int blockSize,
             float N, float W, float H, Vector &u, Vector &v, Vector &n,
             Point &eye)
    {
        this->backgroundColor.set(backgroundColor);
        this->nRows = nRows;
        this->nCols = nCols;
        this->blockSize = blockSize;
        this->N = N;
        this->W = W;
        this->H = H;
        this->u.set(u);
        this->v.set(v);
        this->n.set(n);
        this->ray.start.set(eye);
        pixmap = new RGBpixel *[nRows];
        pixmap[0] = new RGBpixel[nRows * nCols];
        for (int row = 1; row < nRows; row++)
            pixmap[row] = pixmap[row - 1] + nCols;
    }

    void RayTrace(vector<Sphere> &spheres)
    {

        Color hitColor;
        float t_hit;
        for (int r = 0; r < nRows; r += blockSize) {
            for (int c = 0; c < nCols; c += blockSize) {
                // reset t_hit to be inf (FLT_MAX)
                t_hit = FLT_MAX;
                // calculate the direction of the ray
                Vector dir = n * (-N) + u * (W * (2.0 * c / nCols - 1)) +
                             v * (H * (2.0 * r / nRows - 1));
                ray.dir.set(dir);
                for (auto &s : spheres) {
                    // calculate the inverse of the ray
                    inverseRay.setDir(s.inverse_transform_matrix * ray.dir);
                    inverseRay.setStart(s.inverse_transform_matrix * ray.start);
                    // determine whether there are intersections with objects
                    float dirLength = inverseRay.dir.magnitude();
                    float A = pow(dirLength, 2);
                    float B = 2 * inverseRay.dir.dot(inverseRay.start);
                    float C = pow(inverseRay.start.distFromOrigin(), 2) - 1;
                    float delta = pow(B, 2) - 4 * A * C;

                    // if there is no intersection, select background color
                    if (delta < 0) {
                        if (t_hit == FLT_MAX) hitColor.set(backgroundColor);
                    }
                    // if there is exact one intersection
                    else if (delta < FLT_MIN) {
                        float t = -B / (2 * A);
                        if (t < t_hit) {
                            t_hit = t;
                            hitColor.set(s.color);
                        }
                    }
                    // if there are intersections, select the smaller one
                    else {
                        float t1 = (-B + sqrt(delta)) / (2 * A);
                        float t2 = (-B - sqrt(delta)) / (2 * A);
                        t1 = t1 >= 0 ? t1 : FLT_MAX;
                        t2 = t2 >= 0 ? t2 : FLT_MAX;
                        t1 = min(t1, t2);
                        if (t1 <= t_hit) {
                            t_hit = t1;
                            hitColor.set(s.color);
                        }
                    }
                }

                // place the color in the rc-th pixel
                for (int i = 0; i < blockSize; ++i) {
                    for (int j = 0; j < blockSize; ++j) {
                        pixmap[r + i][c + j].r = (unsigned char)(hitColor.r * 255);
                        pixmap[r + i][c + j].g = (unsigned char)(hitColor.g * 255);
                        pixmap[r + i][c + j].b = (unsigned char)(hitColor.b * 255);
                    }
                }

                // use `glRectf` to set the color
                // glRasterPos2i(0.0, 0.0);
                // glColor4f(hitColor.r, hitColor.g, hitColor.b, hitColor.a);
                // float x1 = ((float)c / nCols - 1.0 / 2) * 0.50;
                // float y1 = ((float)r / nRows - 1.0 / 2) * 0.40;
                // float x2 = ((float)(c + blockSize) / nCols - 1.0 / 2) * 0.50;
                // float y2 = ((float)(r + blockSize) / nRows - 1.0 / 2) * 0.40;
                // glRectf(x1, y1, x2, y2);
            }
        }

        // use pixmap and glDrawPixels to set the color of each rc-th pixel to
        // be the color of the object that was hit or the background color
        glRasterPos2f(-0.25, -0.2);
        glDrawPixels(nCols, nRows, GL_RGB, GL_UNSIGNED_BYTE, pixmap[0]);
    }
};

#endif
