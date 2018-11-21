// ray.h
// Implementation for Ray and RayCast Class
// COSC 5450 Project 3a/3b/3c
// Libao Jin
// ljin1@uwyo.edu
// Updated date: 11/20/2018

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
#define OPAQUENESS_THRESHOLD 1.0

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

    void cast(vector<Object> &objects, vector<Light> &lights, int level = 3, bool isPerspectiveProjection = false, bool addEmission = false, bool addRefraction = false, bool addShadow = false)
    {
        for (int r = 0; r < nRows; r += blockSize) {
            for (int c = 0; c < nCols; c += blockSize) {
                // calculate the direction of the ray perspective projection
                if (isPerspectiveProjection) {
                    ray.dir = n * (-N) + u * (W * (2.0 * c / nCols - 1)) + v * (H * (2.0 * r / nRows - 1));
                    ray.start = eye;
                }
                // orthographic projection
                else {
                    ray.dir = n * (-N);
                    ray.start.set(W * (2.0 * c / nCols - 1),
                                  H * (2.0 * r / nRows - 1),
                                  ray.start.z);
                }
                Color hitColor(shade(ray, objects, lights, addEmission, addRefraction, addShadow, level));
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

    Color shade(Ray ray, vector<Object> &objects, vector<Light> &lights, bool addEmission, bool addRefraction, bool addShadow, int level)
    {
        Color hitColor;
        float t_hit = FLT_MAX;  // set t_hit to be inf (FLT_MAX)
        Object hit_object;
        hitObject(ray, objects, hit_object, t_hit);
        // if there is no hit
        if (t_hit == FLT_MAX)
            hitColor.set(trace(lights, backgroundColor));
        else {
            hitColor.set(trace(lights, ray, objects, hit_object, t_hit, addEmission, addShadow));
            // if the object is shiny enough and the level is greater than 0, then do the reflection
            if (hit_object.material.shininess > SHININESS_THRESHOLD && level > 0) {
                Ray reflectionRay = getReflectionRay(ray, hit_object, t_hit);
                // reflectionColor: the color got from reflection ray
                Color reflectionColor = shade(reflectionRay, objects, lights, addEmission, addRefraction, addShadow, level - 1);
                // noHitColor: the background color
                Color noHitColor(trace(lights, backgroundColor));
                // if reflection ray does hit an object, then add up two colors
                if (reflectionColor != noHitColor)
                    hitColor += reflectionColor;
            }
            // if add refraction is turned on
            if (addRefraction) {
                // if the object is transparent enough then add refraction
                if (hit_object.material.ambient.a <= OPAQUENESS_THRESHOLD && level > 0) {
                    // calculate the refraction ray
                    Ray refractionRay = getRefractionRay(ray, hit_object, t_hit);
                    if (refractionRay.dir.magnitude() > 0) {
                        // use shade recursively to get the color obtained by the refraction ray
                        Color refractionColor = shade(refractionRay, objects, lights, addEmission, addRefraction, addShadow, level - 1);
                        Color noHitColor(trace(lights, backgroundColor));
                        if (refractionColor != noHitColor && refractionColor != hitColor)
                            hitColor += refractionColor * 0.2;
                    }
                }
            }
        }
        return hitColor;
    }

    void hitObject(Ray ray, vector<Object> &objects, Object &hit_object, float &t_hit)
    {
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
                if (delta < 0)
                    continue;
                // if there is exact one intersection
                else if (delta < FLT_MIN) {
                    float t = -B / (2 * A) >= 0 ? -B / (2 * A) : FLT_MAX;
                    if (t < t_hit) {
                        t_hit = t;
                        hit_object.set(o);
                    }
                }
                // if there are intersections, select the smaller one
                else {
                    float t1 = (-B + sqrt(delta)) / (2 * A);
                    float t2 = (-B - sqrt(delta)) / (2 * A);
                    t1 = t1 > 0 ? t1 : FLT_MAX;
                    t2 = t2 > 0 ? t2 : FLT_MAX;
                    t1 = min(t1, t2);
                    // make sure the reflection ray is not hitting the starting point
                    if (t1 < 5e-4)
                        t1 = FLT_MAX;
                    if (t1 < t_hit) {
                        t_hit = t1;
                        hit_object.set(o);
                    }
                }
            }
        }
    }

    Color trace(vector<Light> &lights, Ray ray, vector<Object> objects, Object &o, float t_hit, bool addEmission, bool addShadow)
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
                    // total += l.ambient * o.material.ambient * l.attenuation;
                    if (addShadow) {
                        ray.dir.normalize();
                        Point hitPoint2 = hitPoint - ray.dir * 0.25;
                        if (!isInShadow(hitPoint2, l, objects)) {
                            // add local ambient light
                            total += l.ambient * o.material.ambient * l.attenuation;
                            // add local diffuse light
                            total += l.diffuse * o.material.diffuse * max(0, L.dot(N)) * l.attenuation;
                            // add local specular light
                            total += l.specular * o.material.specular * pow(max(0, H.dot(N)), o.material.shininess) * l.attenuation;
                        }
                    }
                    else {
                        // add local ambient light
                        total += l.ambient * o.material.ambient * l.attenuation;
                        // add local diffuse light
                        total += l.diffuse * o.material.diffuse * max(0, L.dot(N)) * l.attenuation;
                        // add local specular light
                        total += l.specular * o.material.specular * pow(max(0, H.dot(N)), o.material.shininess) * l.attenuation;
                    }
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
            for (auto &l : lights)
                if (l.isGlobalAmbient)
                    total += backgroundColor * l.ambient;
        }
        else
            total.set(backgroundColor);
        return total;
    }

    bool isInShadow(Point hitPoint, Light light, vector<Object> objects)
    {
        // calculate the shadow ray
        Vector dir(light.position - hitPoint);
        dir.normalize();
        Ray shadowFeeler(hitPoint, dir);
        Object hit_object;
        // check whether the light was blocked
        float t_hit = FLT_MAX;
        hitObject(shadowFeeler, objects, hit_object, t_hit);
        if (t_hit == FLT_MAX)
            return false;
        else 
            return true;
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
        Point hitPoint0(getHitPoint(ray.start, ray.dir, t_hit));
        ray.dir.normalize();
        Point hitPoint = hitPoint0 + ray.dir * 0.25;
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
        rd.normalize();
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
        rd.normalize();
        Ray reflectionRay(hitPoint, rd);
        return reflectionRay;
    }
};

#endif
