#include <GL/glut.h>

#include "gl.hpp"
#include "RecoveryPoint.hpp"
#include "Triple.hpp"

//#define DEBUG_RECOVERYPOINT

#ifdef DEBUG_RECOVERYPOINT
#       include <iostream>
#endif

RecoveryPoint::RecoveryPoint(std::string name, Triple pos, double ang, Triple vel, double vrot):
        Actor(name, pos, ang, vel, vrot)
{
        this->active = true;
}

void RecoveryPoint::draw() {
        if (active) {
                glPushMatrix();
                        glColor4ub(0, 128, 128, 128);
                        glTranslatef(0, 0, 0.5);
                        glCallList(cubo_simple);
                glPopMatrix();
        }
}
