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

    // for spot light
    GLfloat spot_cutoff;
    GLfloat spot_exponent;
    GLfloat direction_x;
    GLfloat direction_y;
    GLfloat direction_z;
    GLfloat direction_h;
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
        GLfloat ambient[] = {ambient_r, ambient_g, ambient_b, ambient_i};
        GLfloat diffuse[] = {diffuse_r, diffuse_g, diffuse_b, diffuse_i};
        GLfloat specular[] = {specular_r, specular_g, specular_b, specular_i};
        GLfloat position[] = {position_x, position_y, position_z, position_h};
        glLightfv(light, GL_AMBIENT, ambient);
        glLightfv(light, GL_DIFFUSE, diffuse);
        glLightfv(light, GL_SPECULAR, specular);
        glLightfv(light, GL_POSITION, position);
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
        GLfloat ambient[] = {ambient_r, ambient_g, ambient_b, ambient_i};
        GLfloat diffuse[] = {diffuse_r, diffuse_g, diffuse_b, diffuse_i};
        GLfloat specular[] = {specular_r, specular_g, specular_b, specular_i};
        GLfloat position[] = {position_x, position_y, position_z, position_h};
        glLightfv(light, GL_AMBIENT, ambient);
        glLightfv(light, GL_DIFFUSE, diffuse);
        glLightfv(light, GL_SPECULAR, specular);
        glLightfv(light, GL_POSITION, position);
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
        GLfloat ambient[] = {ambient_r, ambient_g, ambient_b, ambient_i};
        GLfloat diffuse[] = {diffuse_r, diffuse_g, diffuse_b, diffuse_i};
        GLfloat specular[] = {specular_r, specular_g, specular_b, specular_i};
        GLfloat position[] = {position_x, position_y, position_z, position_h};
        glLightfv(light, GL_AMBIENT, ambient);
        glLightfv(light, GL_DIFFUSE, diffuse);
        glLightfv(light, GL_SPECULAR, specular);
        glLightfv(light, GL_POSITION, position);
    }
    void setAmbient(GLfloat ar, GLfloat ag, GLfloat ab, GLfloat ai)
    {
        ambient_r = ar;
        ambient_g = ag;
        ambient_b = ab;
        ambient_i = ai;
        GLfloat ambient[] = {ambient_r, ambient_g, ambient_b, ambient_i};
        glLightfv(light, GL_AMBIENT, ambient);
    }

    void setDiffuse(GLfloat dr, GLfloat dg, GLfloat db, GLfloat di)
    {
        diffuse_r = dr;
        diffuse_g = dg;
        diffuse_b = db;
        diffuse_i = di;
        GLfloat diffuse[] = {diffuse_r, diffuse_g, diffuse_b, diffuse_i};
        glLightfv(light, GL_DIFFUSE, diffuse);
    }

    void setSpecular(GLfloat sr, GLfloat sg, GLfloat sb, GLfloat si)
    {
        specular_r = sr;
        specular_g = sg;
        specular_b = sb;
        specular_i = si;
        GLfloat specular[] = {specular_r, specular_g, specular_b, specular_i};
        glLightfv(light, GL_SPECULAR, specular);
    }

    void setPosition(GLfloat px, GLfloat py, GLfloat pz, GLfloat ph)
    {
        position_x = px;
        position_y = py;
        position_z = pz;
        position_h = ph;
        GLfloat position[] = {position_x, position_y, position_z, position_h};
        glLightfv(light, GL_POSITION, position);
    }

    void setSpotlight(GLfloat cutoff, GLfloat exponent, GLfloat dx, GLfloat dy,
                      GLfloat dz, GLfloat dh)
    {
        spot_cutoff = cutoff;
        spot_exponent = exponent;
        direction_x = dx;
        direction_y = dy;
        direction_z = dz;
        direction_h = dh;
        GLfloat spot_direction = {direction_x, ditrection_y, direction_z, direction_h};
        glLightf(light, GL_SPOT_CUTOFF, spot_cutoff);
        glLightf(light, GL_SPOT_EXPONENT, spot_exponent);
        glLightfv(light, GL_SPOT_DIRECTION, spot_direction);
    }

    void setGlobalAmbient(GLfloat ar, GLfloat ag, GLfloat, ab, GLfloat ai)
    {
        ambient_r = ar;
        ambient_g = ag;
        ambient_b = ab;
        ambient_i = ai;
        GLfloat global_ambient[] = {ambient_r, ambient_g, ambient_b, ambient_i};
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
    }

    void on() { glEnable(light); }

    void off() { glDisable(light); }
};

#endif
