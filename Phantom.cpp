#include "Phantom.hpp"

#include <GL/glut.h>

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

Phantom::Phantom(Triple pos, double ang, Triple vel, double vang) {
        this->pos  = pos;
        this->ang  = ang;
        this->vel  = vel;
        this->vrot = vrot;
}

void Phantom::draw() {
        glPushMatrix();
                glColor3ub(0, 255, 0);
                glutSolidCube(1);
        glPopMatrix();
}
