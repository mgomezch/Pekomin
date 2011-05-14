#include "RuntimePekomin.hpp"

#include "gl.hpp"
#include <GL/glut.h>

RuntimePekomin::RuntimePekomin() {
        this->pos  = Triple(0, 0, 0);
        this->ang  = 0;
        this->vel  = Triple(0, 0, 0);
        this->vrot = 0;
}

RuntimePekomin::RuntimePekomin(Triple pos, double ang) {
        this->pos  = pos;
        this->ang  = ang;
        this->vel  = Triple(0, 0, 0);
        this->vrot = 0;
}

RuntimePekomin::RuntimePekomin(Triple pos, double ang, Triple vel, double vang) {
        this->pos  = pos;
        this->ang  = ang;
        this->vel  = vel;
        this->vrot = vrot;
}

void RuntimePekomin::addBehavior(Behavior *b) {
        behaviors.push_back(b);
}

void RuntimePekomin::draw() {
        glColor4ub(255, 0, 0, 255);
        glCallList(cubo);
}

