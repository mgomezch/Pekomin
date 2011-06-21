#include <GL/glut.h>

#include "Phantom.hpp"
#include "gl.hpp"

/*
Phantom::Phantom() {
        this->pos  = Triple(0, 0, 0);
        this->ang  = 0;
        this->vel  = Triple(0, 0, 0);
        this->vrot = 0;
}

Phantom::Phantom(Triple pos, double ang) {
        this->pos  = pos;
        this->ang  = ang;
        this->vel  = Triple(0, 0, 0);
        this->vrot = 0;
}

Phantom::Phantom(Triple pos, double ang, Triple vel, double vrot) {
        this->pos  = pos;
        this->ang  = ang;
        this->vel  = vel;
        this->vrot = vrot;
}

void Phantom::addBehavior(Behavior *b) {
        behaviors.push_back(b);
}
*/

void Phantom::draw() {
        glColor3ub(255, 0, 255);
        glCallList(cubo);
}
