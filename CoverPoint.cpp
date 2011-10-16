#include <GL/glut.h>

#include "gl.hpp"
#include "CoverPoint.hpp"
#include "Triple.hpp"

//#define DEBUG_COVERPOINT

#ifdef DEBUG_COVERPOINT
#       include <iostream>
#endif

CoverPoint::CoverPoint(std::string name, Triple pos, double ang, Triple vel, double vrot):
        Actor(name, pos, ang, vel, vrot),
        active(true)
{}

void CoverPoint::draw() const {
        if (active) {
                glPushMatrix();
                        glColor4ub(105, 105, 105, 128);
                        glTranslatef(0, 0, 0.5);
                        glCallList(cubo_simple);
                glPopMatrix();
        }
}
