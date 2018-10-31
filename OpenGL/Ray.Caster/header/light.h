#ifndef LIGHT_H
#define LIGHT_H

#include "color.h"
#include "matrix.h"

class Light {
public:
    Color ambient;
    Color diffuse;
    Color specular;
    Point position;
    Vector direction;
    bool isPointLight;
    bool isGlobalAmbient;
    // for spot light
    bool isSpotlight;
    float spot_cutoff;
    float spot_exponent;

    Light(const Light &l)
    {
        ambient.set(l.ambient);
        diffuse.set(l.diffuse);
        specular.set(l.specular);
        position.set(l.position);
        direction.set(l.direction);
        isPointLight = l.isPointLight;
        isGlobalAmbient = l.isGlobalAmbient;
        isSpotlight = l.isSpotlight;
        spot_cutoff = l.spot_cutoff;
        spot_exponent = l.spot_exponent;
    }

    Light()
    {
        ambient.set(0.2, 0.2, 0.2, 1);
        diffuse.set(0.2, 0.2, 0.2, 1);
        specular.set(0.2, 0.2, 0.2, 1);
        position.set(0, 1, 0, 1);
        direction.set(0, 0, 0, 0);
        isPointLight = true;
        isGlobalAmbient = false;
        isSpotlight = false;
        spot_cutoff = 90;
        spot_exponent = 1;
    }

    Light(float ar, float ag, float ab, float aa)
    {
        ambient.set(ar, ag, ab, aa);
        diffuse.set(0.2, 0.2, 0.2, 1);
        specular.set(0.2, 0.2, 0.2, 1);
        position.set(0, 1, 0, 1);
        direction.set(1, 1, 1, 0);
        isPointLight = true;
        isGlobalAmbient = false;
        isSpotlight = false;
        spot_cutoff = 90;
        spot_exponent = 1;
    }

    Light(Color &a)
    {
        ambient.set(a);
        diffuse.set(0.2, 0.2, 0.2, 1);
        specular.set(0.2, 0.2, 0.2, 1);
        position.set(0, 1, 0, 1);
        direction.set(1, 1, 1, 0);
        isPointLight = false;
        isGlobalAmbient = true;
        isSpotlight = false;
        spot_cutoff = 90;
        spot_exponent = 1;
    }

    Light(float ar, float ag, float ab, float aa, float dr, float dg, float db,
          float da, float sr, float sg, float sb, float si, float px, float py,
          float pz, float ph)
    {
        ambient.set(ar, ag, ab, aa);
        diffuse.set(dr, dg, db, da);
        specular.set(sr, sg, sb, si);
        position.set(px, py, pz, ph);
        isPointLight = ph == 1;
        if (isPointLight)
            direction.set(1, 1, 1, 0);
        else
            direction.set(px, py, pz, ph);
        isGlobalAmbient = false;
        isSpotlight = false;
        spot_cutoff = 90;
        spot_exponent = 1;
    }

    Light(float ar, float ag, float ab, float aa, float dr, float dg, float db,
          float da, float sr, float sg, float sb, float si, float px, float py,
          float pz, float ph, float dx, float dy, float dz, float dh,
          float cutoff, float exponent)
    {
        ambient.set(ar, ag, ab, aa);
        diffuse.set(dr, dg, db, da);
        specular.set(sr, sg, sb, si);
        position.set(px, py, pz, ph);
        isPointLight = ph == 1;
        if (isPointLight) {
            if (dh == 1)
                direction.set(dx - px, dy - py, dz - pz, 0);
            else
                direction.set(dx, dy, dz, dh);
        }
        else
            direction.set(px, py, pz, ph);
        isGlobalAmbient = false;
        isSpotlight = true;
        spot_cutoff = cutoff;
        spot_exponent = exponent;
    }

    Light(Color &a, Color &d, Color &s, Point &p)
    {
        ambient.set(a);
        diffuse.set(d);
        specular.set(s);
        position.set(p);
        isPointLight = p.h == 1;
        if (isPointLight)
            direction.set(1, 1, 1, 0);
        else
            direction.set(p.x, p.y, p.z, p.h);
        isGlobalAmbient = false;
        isSpotlight = false;
        spot_cutoff = 90;
        spot_exponent = 1;
    }

    void set(float ar, float ag, float ab, float aa, float dr, float dg,
             float db, float da, float sr, float sg, float sb, float si,
             float px, float py, float pz, float ph)
    {
        ambient.set(ar, ag, ab, aa);
        diffuse.set(dr, dg, db, da);
        specular.set(sr, sg, sb, si);
        position.set(px, py, pz, ph);
        isPointLight = ph == 1;
        if (isPointLight)
            direction.set(1, 1, 1, 0);
        else
            direction.set(px, py, pz, ph);
        isGlobalAmbient = false;
        isSpotlight = false;
        spot_cutoff = 90;
        spot_exponent = 1;
    }

    void set(float ar, float ag, float ab, float aa, float dr, float dg, float db,
          float da, float sr, float sg, float sb, float si, float px, float py,
          float pz, float ph, float dx, float dy, float dz, float dh,
          float cutoff, float exponent)
    {
        ambient.set(ar, ag, ab, aa);
        diffuse.set(dr, dg, db, da);
        specular.set(sr, sg, sb, si);
        position.set(px, py, pz, ph);
        isPointLight = ph == 1;
        if (isPointLight) {
            if (dh == 1)
                direction.set(dx - px, dy - py, dz - pz, 0);
            else
                direction.set(dx, dy, dz, dh);
        }
        else
            direction.set(px, py, pz, ph);
        isGlobalAmbient = false;
        isSpotlight = true;
        spot_cutoff = cutoff;
        spot_exponent = exponent;
    }

    void set(Color &a, Color &d, Color &s, Point &p)
    {
        ambient.set(a);
        diffuse.set(d);
        specular.set(s);
        position.set(p);
        isPointLight = p.h == 1;
        if (isPointLight)
            direction.set(1, 1, 1, 0);
        else
            direction.set(p.x, p.y, p.z, p.h);
        isGlobalAmbient = false;
        isSpotlight = false;
        spot_cutoff = 90;
        spot_exponent = 1;
    }

    void setAmbient(float ar, float ag, float ab, float aa)
    {
        ambient.set(ar, ag, ab, aa);
    }

    void setAmbient(Color &a) { ambient.set(a.r, a.g, a.b, a.a); }

    void setDiffuse(float dr, float dg, float db, float da)
    {
        diffuse.set(dr, dg, db, da);
    }

    void setDiffuse(Color &d) { diffuse.set(d.r, d.g, d.b, d.a); }

    void setSpecular(float sr, float sg, float sb, float si)
    {
        specular.set(sr, sg, sb, si);
    }

    void setSpecular(Color &s) { specular.set(s.r, s.g, s.b, s.a); }

    void setPosition(float px, float py, float pz, float ph)
    {
        position.set(px, py, pz, ph);
    }

    void setPosition(Point &p) { position.set(p.x, p.y, p.z, p.h); }

    void setDirection(float dx, float dy, float dz, float dh)
    {
        direction.set(dx, dy, dz, dh);
    }

    void setDirection(Vector &d) { direction.set(d.x, d.y, d.z, d.h); }

    void setSpotlight(float cutoff, float exponent, float dx, float dy,
                      float dz, float dh)
    {
        isGlobalAmbient = false;
        isSpotlight = true;
        spot_cutoff = cutoff;
        spot_exponent = exponent;
        direction.set(dx, dy, dz, dh);
    }
};

#endif
