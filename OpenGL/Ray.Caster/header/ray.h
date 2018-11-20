// ray.h
// Implementation for Ray and RayCast Class
// COSC 5450 Project 3a/3b/3c
// Libao Jin
// ljin1@uwyo.edu
// Updated date: 11/19/2018

#ifndef RAY_H
#define RAY_H

#include "light.h"
#include "object.h"
#include <cfloat>
#include <iostream>
#include <vector>

#if defined _WIN32 || defined WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
// #include <gl/glut.h>
#include "glut.h"
#elif defined __APPLE__ && !defined X11
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

#ifndef PROJECT
#define PROJECT "proj3c"
#endif

#define SHININESS_THRESHOLD 0.5

#define max(a, b) (a > b ? a : b)

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

    void cast(vector<Object> &objects, vector<Light> &lights, int level = 3, bool isPerspectiveProjection = false, bool addEmission = false)
    {
        for (int r = 0; r < nRows; r += blockSize) {
            for (int c = 0; c < nCols; c += blockSize) {
                // calculate the direction of the ray perspective projection
                if (isPerspectiveProjection) {
                    ray.dir = n * (-N) + u * (W * (2.0 * c / nCols - 1)) +
                              v * (H * (2.0 * r / nRows - 1));
                    ray.start = eye;
                }
                // orthographic projection
                else {
                    ray.dir = n * (-N);
                    ray.start.set(W * (2.0 * c / nCols - 1),
                                  H * (2.0 * r / nRows - 1),
                                  ray.start.z);
                }
                Color hitColor(shade(ray, objects, lights, addEmission, level));
                // place the color in the rc-th pixel
                for (int i = 0; i < blockSize; ++i) {
                    for (int j = 0; j < blockSize; ++j) {
                        pixmap[r + i][c + j].r = (unsigned char)(hitColor.r * 255);
                        pixmap[r + i][c + j].g = (unsigned char)(hitColor.g * 255);
                        pixmap[r + i][c + j].b = (unsigned char)(hitColor.b * 255);
                    }
                }
            }
        }

        // use pixmap and glDrawPixels to set the color of each rc-th pixel to
        // be the color of the object that was hit or the background color
        glRasterPos2f(-0.25, -0.2);
        glDrawPixels(nCols, nRows, GL_RGB, GL_UNSIGNED_BYTE, pixmap[0]);
    }

    Color shade(Ray ray, vector<Object> &objects, vector<Light> &lights, bool addEmission, int level)
    {
        Color hitColor;
        float t_hit = FLT_MAX;  // set t_hit to be inf (FLT_MAX)
        for (auto &o : objects) {
            // calculate the inverse of the ray
            inverseRay.setDir(o.inverse_transform_matrix * ray.dir);
            inverseRay.setStart(o.inverse_transform_matrix * ray.start);
            // determine whether there are intersections with objects
            if (o.type == "sphere") {
                float dirLength = inverseRay.dir.magnitude();
                float A = pow(dirLength, 2);
                float B = 2 * inverseRay.dir.dot(inverseRay.start);
                float C = pow(inverseRay.start.distFromOrigin(), 2) - 1;
                float delta = pow(B, 2) - 4 * A * C;
                // if there is no intersection, select background color
                if (delta < 0) {
                    if (t_hit == FLT_MAX)
                        hitColor.set(trace(lights, backgroundColor));
                }
                // if there is exact one intersection
                else if (delta < FLT_MIN) {
                    float t =
                        -B / (2 * A) >= 0 ? -B / (2 * A) : FLT_MAX;
                    if (t < t_hit) {
                        t_hit = t;
                        hitColor.set(trace(lights, ray, o, t_hit, addEmission));
                    }
                }
                // if there are intersections, select the smaller one
                else {
                    float t1 = (-B + sqrt(delta)) / (2 * A);
                    float t2 = (-B - sqrt(delta)) / (2 * A);
                    t1 = t1 > 0 ? t1 : FLT_MAX;
                    t2 = t2 > 0 ? t2 : FLT_MAX;
                    t1 = min(t1, t2);
                    // make sure the ray is
                    if (t1 <= 1e-3)
                        t1 = FLT_MAX;
                    if (t1 < t_hit) {                        t_hit = t1;
                        hitColor.set(trace(lights, ray, o, t_hit, addEmission));
                        // if the object is shiny enough and the level is greater than 0, then do the reflection
                        if (o.material.shininess > SHININESS_THRESHOLD && level > 0) {
                            Ray reflectionRay = getReflectionRay(ray, o, t_hit);
                            // reflectionColor: the color got from reflection ray
                            Color reflectionColor = shade(reflectionRay, objects, lights, addEmission, level - 1);
                            // noHitColor: the background color
                            Color noHitColor(trace(lights, backgroundColor));
                            // if reflection ray does hit an object, then add up two colors
                            if (reflectionColor != noHitColor)
                                hitColor += reflectionColor;
                        }
                        // Ray refractionRay = getRefractionRay(ray, o, t_hit);
                        // if (refractionRay.dir.magnitude() > 0 && level > 0)
                        //     hitColor += shade(refractionRay, objects, lights, addEmission, level - 1);
                    }
                }
            }
            /*
            // when the object is a cylinder, similar to spheres
            else if (o.type == "cylinder") {
                Vector dir2d(inverseRay.dir.x, 0.0, inverseRay.dir.z);
                Point center2d(inverseRay.start.x, 0.0, inverseRay.start.z);
                float A = pow(dir2d.magnitude(), 2);
                float B = dir2d.dot(center2d) * 2;
                float C = pow(center2d.distFromOrigin(), 2) - 1;
                float delta = pow(B, 2) - 4 * A * C;
                if (delta < 0) {
                    if (t_hit == FLT_MAX)
                        hitColor.set(trace(lights, backgroundColor));
                }
                else if (delta < FLT_MIN) {
                    float t =
                        -B / (2 * A) >= 0 ? -B / (2 * A) : FLT_MAX;
                    if (t < t_hit) {
                        float yy =
                            inverseRay.start.y + inverseRay.dir.y * t;
                        if (yy >= 0 && yy <= 1.0) {
                            t_hit = t;
                            hitColor.set(trace(lights, ray, o, t_hit, addEmission));
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
                        float yy = inverseRay.start.y + inverseRay.dir.y * t1;
                        if (yy >= 0 && yy <= 1.0) {
                            t_hit = t1;
                            hitColor.set(trace(lights, ray, o, t_hit, addEmission));
                        }
                    }
                }
            }
            */
        }
        return hitColor;
    }

    Color trace(vector<Light> &lights, Ray &ray, Object &o, float t_hit, bool addEmission)
    {
        Color total;
        if (strcmp(PROJECT, "proj3a") != 0) {
            Point hitPoint = getHitPoint(ray.start, ray.dir, t_hit);
            Vector V = getV(hitPoint, ray.start);
            Vector N = getNormal(o, hitPoint);
            for (auto &l : lights) {
                Vector L = getL(l.position, hitPoint);
                Vector R = getR(N, L);
                Vector H = getH(V, L);
                // global ambient light
                if (l.isGlobalAmbient) {
                    total += l.ambient * o.material.ambient;
                }
                else {
                    l.attenuation = getAttenuation(l, hitPoint);
                    // add local ambient light
                    total += l.ambient * o.material.ambient * l.attenuation;
                    // add local diffuse light
                    total += l.diffuse * o.material.diffuse * max(0, L.dot(N)) * l.attenuation;
                    // add local specular light
                    total += l.specular * o.material.specular * pow(max(0, H.dot(N)), o.material.shininess) * l.attenuation;
                }
            }
        }
        if (strcmp(PROJECT, "proj3a") == 0 || addEmission) {
            // for project 3a, set the color of the sphere
            total += o.material.emission;
        }
        return total;
    }

    // calculate the background color if the ray does not hit the object
    Color trace(vector<Light> &lights, Color backgroundColor)
    {
        Color total;
        if (strcmp(PROJECT, "proj3a") != 0) {
            for (auto &l : lights) {
                if (l.isGlobalAmbient) {
                    total += backgroundColor * l.ambient;
                }
            }
        }
        else {
            total.set(backgroundColor);
        }
        return total;
    }

    // calcuculate the hit point
    Point getHitPoint(Point start, Vector dir, float t_hit)
    {
        Point hitPoint;
        hitPoint.set(start + dir * t_hit);
        return hitPoint;
    }

    // direction vector from the point on the surface toward each light source
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

    // calculate normal vector on the surface of the sphere
    Vector getNormal(Object o, Point hitPoint)
    {
        Vector N(hitPoint - o.center);
        N.normalize();
        return N;
    }

    // calculate reflection vector
    Vector getR(Vector N, Vector L)
    {
        Vector R(N * (N.dot(L) * 2) - L);
        R.normalize();
        return R;
    }

    // calculate view vector
    Vector getV(Point hitPoint, Point start)
    {
        Vector V(start - hitPoint);
        V.normalize();
        return V;
    }

    // calculate halfway vector
    Vector getH(Vector V, Vector L)
    {
        V.normalize();
        L.normalize();
        Vector H(V + L);
        H.normalize();
        return H;
    }

    float getAttenuation(Light light, Point hitPoint, float c = 1.0, float l = 0.02, float q = 0.0001)
    {
        Vector L(hitPoint - light.position);
        Vector D(light.direction);
        float d = L.magnitude();
        L.normalize();
        D.normalize();
        float attenuation = 1.0;
        if (light.isPointLight) {
            // attenuation = 1 / (c + l * d + q * d * d);
            if (light.isSpotlight) {
                attenuation = 1 / (c + l * d + q * d * d);
                // check whether the object can be reached by the spotlight
                if (L.dot(D) < cos(light.spot_cutoff * pi / 180))
                    attenuation *= 0;
                else
                    attenuation *= pow(max(L.dot(D), 0), light.spot_exponent);
            }
        }
        return attenuation;
    }

    Ray getRefractionRay(Ray ray, Object o, float t_hit, float ni = 1, float nt = 2)
    {
        Vector d(ray.dir);
        d.normalize();
        Point hitPoint(getHitPoint(ray.start, ray.dir, t_hit));
        Vector normal(getNormal(o, hitPoint));
        normal.normalize();
        float determinant = 1 - pow(ni, 2) / pow(nt, 2) * (1 - pow(d.dot(normal), 2));
        Vector rd;  // refraction direction
        if (determinant < 0) { // there is no refractoin ray
            rd.set(0, 0, 0);
        }
        else {
           rd.set((d - normal * d.dot(normal)) * (ni / nt) - normal * sqrt(determinant));
        }
        Ray refractionRay(hitPoint, rd);
        return refractionRay;
    }

    Ray getReflectionRay(Ray ray, Object o, float t_hit)
    {
        Point hitPoint(getHitPoint(ray.start, ray.dir, t_hit));
        Vector normal(getNormal(o, hitPoint));
        normal.normalize();
        Vector d(ray.dir);
        d.normalize();
        Vector rd(d - normal * (2 * d.dot(normal)));
        Ray reflectionRay(hitPoint, rd);
        return reflectionRay;
    }
};

#endif
