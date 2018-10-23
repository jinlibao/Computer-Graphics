#ifndef CAMERA_H
#define CAMERA_H

#include "matrix.h"

class Camera {
    private:
        Point eye, look;
        Vector u, v, n, up;
        float H, W, viewAngle, aspect, nearDist, farDist;
        void setModelViewMatrix();

    public:
        Camera() {}
        void set(float, float, float, float, float, float, float, float, float);
        void set(Point& eye, Point& look, Vector& up);
        void roll(float theta);
        void pitch(float theta);
        void yaw(float theta);
        void FocusedPitch(float theta);
        void FocusedYaw(float theta);
        void CenterFocus();
        void slide(float delU, float delV, float delN);
        void setShape(float vAng, float asp, float nearD, float farD);
        Vector GetC(int, int, int, int);
        Point GetEye();
};

#endif
