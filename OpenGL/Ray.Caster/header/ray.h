// ray.h
// Implementation for Ray and RayCast Class
// COSC 5450 Project 3a
// Libao Jin
// ljin1@uwyo.edu
// 10/29/2018

#ifndef RAY_H
#define RAY_H

#include "light.h"
#include "object.h"
#include <cfloat>
#include <iostream>
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

#define max(a, b) (a > b ? a : b)
#define LIGHTSON true
// #define LIGHTSON false

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
    Point eye, look;
    Vector up;

    RayCast(){};

    void set(Color &backgroundColor, int nCols, int nRows, int blockSize,
             float N, float W, float H, Point &eye, Point &look, Vector &up)
    {
        this->backgroundColor.set(backgroundColor);
        this->nRows = nRows;
        this->nCols = nCols;
        this->blockSize = blockSize;
        this->N = N;
        this->W = W;
        this->H = H;
        this->eye = eye;
        this->look = look;
        this->up = up;
        // calculate v, n, u vectors for later use
        n = eye - look;
        u = up.cross(n);
        v = n.cross(u);
        n.normalize();
        u.normalize();
        v.normalize();
        pixmap = new RGBpixel *[nRows];
        pixmap[0] = new RGBpixel[nRows * nCols];
        for (int row = 1; row < nRows; row++)
            pixmap[row] = pixmap[row - 1] + nCols;
    }

    void cast(vector<Object> &objects, vector<Light> &lights,
              bool isPerspectiveProjection = true)
    {

        Color hitColor;
        float t_hit;
        for (int r = 0; r < nRows; r += blockSize) {
            for (int c = 0; c < nCols; c += blockSize) {
                // reset t_hit to be inf (FLT_MAX)
                t_hit = FLT_MAX;
                // calculate the direction of the ray
                // perspective projection
                if (isPerspectiveProjection) {
                    ray.dir = n * (-N) + u * (W * (2.0 * c / nCols - 1)) +
                              v * (H * (2.0 * r / nRows - 1));
                    ray.start = eye;
                }
                // orthographic projection
                else {
                    ray.dir = n * (-N);
                    ray.start.set(W * (2.0 * c / nCols - 1),
                                  H * (2.0 * r / nRows - 1), ray.start.z);
                }
                for (auto &o : objects) {
                    // calculate the inverse of the ray
                    inverseRay.setDir(o.inverse_transform_matrix * ray.dir);
                    inverseRay.setStart(o.inverse_transform_matrix * ray.start);
                    if (o.type == "sphere") {
                        // determine whether there are intersections with
                        // objects
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
                                hitColor.set(trace(lights, ray, o, t_hit));
                            }
                        }
                        // if there are intersections, select the smaller one
                        else {
                            float t1 = (-B + sqrt(delta)) / (2 * A);
                            float t2 = (-B - sqrt(delta)) / (2 * A);
                            t1 = t1 >= 0 ? t1 : FLT_MAX;
                            t2 = t2 >= 0 ? t2 : FLT_MAX;
                            t1 = min(t1, t2);
                            if (t1 < t_hit) {
                                t_hit = t1;
                                hitColor.set(trace(lights, ray, o, t_hit));
                            }
                        }
                    }
                    // when the object is a cylinder, very similar to the case
                    // of sphere
                    else if (o.type == "cylinder") {
                        Vector dir2d(inverseRay.dir.x, 0.0, inverseRay.dir.z);
                        Point center2d(inverseRay.start.x, 0.0,
                                       inverseRay.start.z);
                        float A = pow(dir2d.magnitude(), 2);
                        float B = dir2d.dot(center2d) * 2;
                        float C = pow(center2d.distFromOrigin(), 2) - 1;
                        float delta = pow(B, 2) - 4 * A * C;
                        if (delta < 0) {
                            if (t_hit == FLT_MAX) hitColor.set(backgroundColor);
                        }
                        else if (delta < FLT_MIN) {
                            float t = -B / (2 * A);
                            if (t < t_hit) {
                                float yy =
                                    inverseRay.start.y + inverseRay.dir.y * t;
                                if (yy >= 0 && yy <= 1.0) {
                                    t_hit = t;
                                    hitColor.set(trace(lights, ray, o, t_hit));
                                }
                            }
                        }
                        else {
                            float t1 = (-B + sqrt(delta)) / (2 * A);
                            float t2 = (-B - sqrt(delta)) / (2 * A);
                            t1 = t1 > 0 ? t1 : FLT_MAX;
                            t2 = t2 > 0 ? t2 : FLT_MAX;
                            t1 = min(t1, t2);
                            if (t1 < t_hit) {
                                float yy =
                                    inverseRay.start.y + inverseRay.dir.y * t1;
                                if (yy >= 0 && yy <= 1.0) {
                                    t_hit = t1;
                                    hitColor.set(trace(lights, ray, o, t_hit));
                                }
                            }
                        }
                    }
                }

                // place the color in the rc-th pixel
                for (int i = 0; i < blockSize; ++i) {
                    for (int j = 0; j < blockSize; ++j) {
                        pixmap[r + i][c + j].r =
                            (unsigned char)(hitColor.r * 255);
                        pixmap[r + i][c + j].g =
                            (unsigned char)(hitColor.g * 255);
                        pixmap[r + i][c + j].b =
                            (unsigned char)(hitColor.b * 255);
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
        // glRasterPos2f(-0.25, -0.2);
        glRasterPos2f(-0.25, -0.2);
        glDrawPixels(nCols, nRows, GL_RGB, GL_UNSIGNED_BYTE, pixmap[0]);
    }

    Color trace(vector<Light> &lights, Ray &ray, Object &o, float t_hit)
    {
        // Color total(o.material.emission);
        Color total;

        if (LIGHTSON) {
            Point hitPoint = getHitPoint(ray.start, ray.dir, t_hit);
            Vector V = getV(hitPoint, ray.start);
            Vector N = getNormal(o, hitPoint);
            for (auto &l : lights) {
                Vector L = getL(l.position, hitPoint);
                Vector R = getR(N, L);
                Vector H = getH(V, L);
                if (l.isGlobalAmbient) {
                    total += l.ambient * o.material.ambient;
                }
                else {
                    l.attenuation = getAttenuation(l, hitPoint);
                    total += l.ambient * o.material.ambient;
                    total += l.diffuse * o.material.diffuse * max(0, L.dot(N)) * l.attenuation;
                    // total += l.specular * o.material.specular * pow(max(0, R.dot(V)), o.material.shininess) * l.attenuation;
                    total += l.specular * o.material.specular * pow(max(0, H.dot(N)), o.material.shininess) * l.attenuation;
                }
            }
        }
        return total;
    }

    Point getHitPoint(Point start, Vector dir, float t_hit)
    {
        Point hitPoint;
        hitPoint.set(start + dir * t_hit);
        return hitPoint;
    }

    // the direction vector from the point on the surface toward each light
    // source
    Vector getL(Point lightPos, Point hitPoint)
    {
        Vector L;
        if (lightPos.h == 0)
            L.set(lightPos.x, lightPos.y, lightPos.z);
        else
            L.set(lightPos - hitPoint);
        L.normalize();
        return L;
    }

    Vector getNormal(Object o, Point hitPoint)
    {
        Vector N(hitPoint - o.center);
        N.normalize();
        return N;
    }

    Vector getR(Vector N, Vector L)
    {
        Vector R(N * (N.dot(L) * 2) - L);
        R.normalize();
        return R;
    }

    Vector getV(Point hitPoint, Point start)
    {
        Vector V(start - hitPoint);
        V.normalize();
        return V;
    }

    Vector getH(Vector V, Vector L)
    {
        V.normalize();
        L.normalize();
        Vector H(V + L);
        H.normalize();
        return H;
    }

    float getAttenuation(Light light, Point hitPoint, float c = 0.15, float l = 0.05, float q = 0.05)
    {
        Vector L(hitPoint - light.position);
        Vector D(light.direction);
        float d = L.magnitude();
        L.normalize();
        D.normalize();
        float attenuation = 1.0;
        if (light.isPointLight) {
            attenuation = 1 / (c + l * d + q * d * d);
            if (light.isSpotlight) {
                if (L.dot(D) < cos(light.spot_cutoff * pi / 180))
                    attenuation *= 0;
                else
                    attenuation *= pow(max(L.dot(D), 0), light.spot_exponent);
            }
        }
        return attenuation;
    }
};

#endif
