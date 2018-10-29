#ifndef MATERIAL_H
#define MATERIAL_H

#include "matrix.h"

#if defined __APPLE__ && !defined X11
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

class Material {
private:
    GLfloat ambient_r;
    GLfloat ambient_g;
    GLfloat ambient_b;
    GLfloat ambient_i;
    GLfloat diffuse_r;
    GLfloat diffuse_g;
    GLfloat diffuse_b;
    GLfloat diffuse_i;
    GLfloat specular_r;
    GLfloat specular_g;
    GLfloat specular_b;
    GLfloat specular_i;
    GLfloat emission_r;
    GLfloat emission_g;
    GLfloat emission_b;
    GLfloat emission_i;
    GLfloat shininess;

public:
    Material()
    {
        ambient_r = 0.2;
        ambient_g = 0.2;
        ambient_b = 0.2;
        ambient_i = 1.0;
        diffuse_r = 0.2;
        diffuse_g = 0.2;
        diffuse_b = 0.2;
        diffuse_i = 1.0;
        specular_r = 0.2;
        specular_g = 0.2;
        specular_b = 0.2;
        specular_i = 1.0;
        emission_r = 0.0;
        emission_g = 0.0;
        emission_b = 0.0;
        emission_i = 0.0;
        shininess = 0.0;
    }

    Material(GLfloat ar, GLfloat ag, GLfloat ab, GLfloat ai, GLfloat dr,
             GLfloat dg, GLfloat db, GLfloat di, GLfloat sr, GLfloat sg,
             GLfloat sb, GLfloat si, GLfloat er, GLfloat eg, GLfloat eb,
             GLfloat ei, GLfloat s)
    {
        ambient_r = ar;
        ambient_g = ag;
        ambient_b = ab;
        ambient_i = ai;
        diffuse_r = dr;
        diffuse_g = dg;
        diffuse_b = db;
        diffuse_i = di;
        specular_r = sr;
        specular_g = sg;
        specular_b = sb;
        specular_i = si;
        emission_r = er;
        emission_g = eg;
        emission_b = eb;
        emission_i = ei;
        shininess = s;
    }

    void active()
    {
        GLfloat ambient[] = {ambient_r, ambient_g, ambient_b, ambient_i};
        GLfloat diffuse[] = {diffuse_r, diffuse_g, diffuse_b, diffuse_i};
        GLfloat specular[] = {specular_r, specular_g, specular_b, specular_i};
        GLfloat emission[] = {emission_r, emission_g, emission_b, emission_i};
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
        glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
    }
};

#endif
