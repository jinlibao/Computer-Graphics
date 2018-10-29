#ifndef CAMERA_H
#define CAMERA_H

#include "matrix.h"

class Camera {
public:
    Point eye, look;
    Vector u, v, n, up;
    float H, W, viewAngle, aspect, nearDist, farDist;
    void setModelViewMatrix();

    Camera() {}
    void set(float, float, float, float, float, float, float, float, float);
    void set(Point &eye, Point &look, Vector &up);
    void slide(float delU, float delV, float delN);
    void setShape(float vAng, float asp, float nearD, float farD);
    void roll(float theta);
    void pitch(float theta);
    void yaw(float theta);
    void FocusedPitch(float theta);
    void FocusedYaw(float theta);
    void CenterFocus();
    void raytrace(int blockSize);
    Vector GetC(int, int, int, int);
    Point GetEye();
    Point GetLook();
    Vector GetN();
    Vector GetV();
    Vector GetU();
    float GetAspect();
};

#endif
