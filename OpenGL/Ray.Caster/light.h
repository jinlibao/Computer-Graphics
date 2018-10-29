#ifndef LIGHT_H
#define LIGHT_H

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

class Light {
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
    GLfloat position_x;
    GLfloat position_y;
    GLfloat position_z;
    GLfloat position_h;
    GLenum light;

public:
    Light()
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
        position_x = 1.0;
        position_y = 1.0;
        position_z = 1.0;
        position_h = 0.0; // directional light
        light = GL_LIGHT0;
    }

    Light(GLfloat ar, GLfloat ag, GLfloat ab, GLfloat ai, GLfloat dr,
          GLfloat dg, GLfloat db, GLfloat di, GLfloat sr, GLfloat sg,
          GLfloat sb, GLfloat si, GLfloat px, GLfloat py, GLfloat pz,
          GLfloat ph, GLenum light)
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
        position_x = px;
        position_y = py;
        position_z = pz;
        position_h = ph;
        this->light = light;
    }

    void set(GLfloat ar, GLfloat ag, GLfloat ab, GLfloat ai, GLfloat dr,
             GLfloat dg, GLfloat db, GLfloat di, GLfloat sr, GLfloat sg,
             GLfloat sb, GLfloat si, GLfloat px, GLfloat py, GLfloat pz,
             GLfloat ph, GLenum light)
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
        position_x = px;
        position_y = py;
        position_z = pz;
        position_h = ph;
        this->light = light;
    }
    void setAmbient(GLfloat ar, GLfloat ag, GLfloat ab, GLfloat ai)
    {
        ambient_r = ar;
        ambient_g = ag;
        ambient_b = ab;
        ambient_i = ai;
    }

    void setDiffuse(GLfloat dr, GLfloat dg, GLfloat db, GLfloat di)
    {
        diffuse_r = dr;
        diffuse_g = dg;
        diffuse_b = db;
        diffuse_i = di;
    }

    void setSpecular(GLfloat sr, GLfloat sg, GLfloat sb, GLfloat si)
    {
        specular_r = sr;
        specular_g = sg;
        specular_b = sb;
        specular_i = si;
    }

    void setPosition(GLfloat px, GLfloat py, GLfloat pz, GLfloat ph)
    {
        position_x = px;
        position_y = py;
        position_z = pz;
        position_h = ph;
    }

    void on()
    {
        GLfloat ambient[] = {ambient_r, ambient_g, ambient_b, ambient_i};
        GLfloat diffuse[] = {diffuse_r, diffuse_g, diffuse_b, diffuse_i};
        GLfloat specular[] = {specular_r, specular_g, specular_b, specular_i};
        GLfloat position[] = {position_x, position_y, position_z, position_h};
        glLightfv(light, GL_AMBIENT, ambient);
        glLightfv(light, GL_DIFFUSE, diffuse);
        glLightfv(light, GL_SPECULAR, specular);
        glLightfv(light, GL_POSITION, position);
        glEnable(light);
    }

    void off() { glDisable(light); }
};

#endif
