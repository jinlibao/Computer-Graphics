// material.h
// Implementation for Material Class
// COSC 5450 Project 3b/3c
// Libao Jin
// Updated date: 11/02/2018

#ifndef MATERIAL_H
#define MATERIAL_H

#include "color.h"
#include "matrix.h"

class Material {
public:
    Color ambient;
    Color diffuse;
    Color specular;
    Color emission;
    float shininess;
    float attenuation;

    Material(const Material &m)
    {
        ambient.set(m.ambient);
        diffuse.set(m.diffuse);
        specular.set(m.specular);
        emission.set(m.emission);
        shininess = m.shininess;
        attenuation = m.attenuation;
    }

    Material()
    {
        ambient.set(0.2, 0.2, 0.2, 1);
        diffuse.set(0.2, 0.2, 0.2, 1);
        specular.set(0.2, 0.2, 0.2, 1);
        emission.set(0, 1, 0, 1);
        shininess = 1;
        attenuation = 1;
    }

    Material(float er, float eg, float eb)
    {
        ambient.set(0.2, 0.2, 0.2, 1);
        diffuse.set(0.2, 0.2, 0.2, 1);
        specular.set(0.2, 0.2, 0.2, 1);
        emission.set(er, eg, eb, 1);
        shininess = 1;
        attenuation = 1;
    }

    Material(float er, float eg, float eb, float ea)
    {
        ambient.set(0.2, 0.2, 0.2, 1);
        diffuse.set(0.2, 0.2, 0.2, 1);
        specular.set(0.2, 0.2, 0.2, 1);
        emission.set(er, eg, eb, ea);
        shininess = 1;
        attenuation = 1;
    }

    Material(Color &e)
    {
        ambient.set(0.2, 0.2, 0.2, 1);
        diffuse.set(0.2, 0.2, 0.2, 1);
        specular.set(0.2, 0.2, 0.2, 1);
        emission.set(e);
        shininess = 1;
        attenuation = 1;
    }

    Material(float ar, float ag, float ab, float aa, float dr, float dg,
             float db, float da, float sr, float sg, float sb, float si,
             float shininess)
    {
        ambient.set(ar, ag, ab, aa);
        diffuse.set(dr, dg, db, da);
        specular.set(sr, sg, sb, si);
        this->shininess = shininess;
        attenuation = 1;
    }

    Material(float ar, float ag, float ab, float aa, float dr, float dg,
             float db, float da, float sr, float sg, float sb, float si,
             float er, float eg, float eb, float ea)
    {
        ambient.set(ar, ag, ab, aa);
        diffuse.set(dr, dg, db, da);
        specular.set(sr, sg, sb, si);
        emission.set(er, eg, eb, ea);
        shininess = 1;
        attenuation = 1;
    }

    Material(float ar, float ag, float ab, float aa, float dr, float dg,
             float db, float da, float sr, float sg, float sb, float si,
             float er, float eg, float eb, float ea, float sh)
    {
        ambient.set(ar, ag, ab, aa);
        diffuse.set(dr, dg, db, da);
        specular.set(sr, sg, sb, si);
        emission.set(er, eg, eb, ea);
        shininess = sh;
        attenuation = 1;
    }

    Material(float ar, float ag, float ab, float aa, float dr, float dg,
             float db, float da, float sr, float sg, float sb, float si,
             float er, float eg, float eb, float ea, float dx, float dy,
             float dz, float dh, float shin, float erponent)
    {
        ambient.set(ar, ag, ab, aa);
        diffuse.set(dr, dg, db, da);
        specular.set(sr, sg, sb, si);
        emission.set(er, eg, eb, ea);
        shininess = shin;
        attenuation = erponent;
    }

    Material(Color &a, Color &d, Color &s, Color &e)
    {
        ambient.set(a);
        diffuse.set(d);
        specular.set(s);
        emission.set(e);
        shininess = 1;
        attenuation = 1;
    }

    void set(const Material &m)
    {
        ambient.set(m.ambient);
        diffuse.set(m.diffuse);
        specular.set(m.specular);
        emission.set(m.emission);
        shininess = m.shininess;
        attenuation = m.attenuation;
    }

    void set(float er, float eg, float eb)
    {
        ambient.set(0.2, 0.2, 0.2, 1);
        diffuse.set(0.2, 0.2, 0.2, 1);
        specular.set(0.2, 0.2, 0.2, 1);
        emission.set(er, eg, eb, 1);
        shininess = 1;
        attenuation = 1;
    }

    void set(float er, float eg, float eb, float ea)
    {
        ambient.set(0.2, 0.2, 0.2, 1);
        diffuse.set(0.2, 0.2, 0.2, 1);
        specular.set(0.2, 0.2, 0.2, 1);
        emission.set(er, eg, eb, ea);
        shininess = 1;
        attenuation = 1;
    }

    void set(float ar, float ag, float ab, float aa, float dr, float dg,
             float db, float da, float sr, float sg, float sb, float si,
             float shininess)
    {
        ambient.set(ar, ag, ab, aa);
        diffuse.set(dr, dg, db, da);
        specular.set(sr, sg, sb, si);
        this->shininess = shininess;
        attenuation = 1;
    }

    void set(float ar, float ag, float ab, float aa, float dr, float dg,
             float db, float da, float sr, float sg, float sb, float si,
             float er, float eg, float eb, float ea)
    {
        ambient.set(ar, ag, ab, aa);
        diffuse.set(dr, dg, db, da);
        specular.set(sr, sg, sb, si);
        emission.set(er, eg, eb, ea);
        shininess = 1;
        attenuation = 1;
    }

    void set(float ar, float ag, float ab, float aa, float dr, float dg,
             float db, float da, float sr, float sg, float sb, float si,
             float er, float eg, float eb, float ea, float sh)
    {
        ambient.set(ar, ag, ab, aa);
        diffuse.set(dr, dg, db, da);
        specular.set(sr, sg, sb, si);
        emission.set(er, eg, eb, ea);
        shininess = sh;
        attenuation = 1;
    }

    void set(float ar, float ag, float ab, float aa, float dr, float dg,
             float db, float da, float sr, float sg, float sb, float si,
             float er, float eg, float eb, float ea, float dx, float dy,
             float dz, float dh, float shin, float erponent)
    {
        ambient.set(ar, ag, ab, aa);
        diffuse.set(dr, dg, db, da);
        specular.set(sr, sg, sb, si);
        emission.set(er, eg, eb, ea);
        shininess = shin;
        attenuation = erponent;
    }

    void set(Color &a, Color &d, Color &s, Color &e)
    {
        ambient.set(a);
        diffuse.set(d);
        specular.set(s);
        emission.set(e);
        shininess = 1;
        attenuation = 1;
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

    void setEmission(float er, float eg, float eb, float ea)
    {
        emission.set(er, eg, eb, ea);
    }

    void setEmission(Color &e) { emission.set(e.r, e.g, e.b, e.a); }
};

#endif
