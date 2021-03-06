#include <cmath>
#include <GL/glut.h>

#include "gl.hpp"
#include "RuntimeBox.hpp"
#include "Triple.hpp"

//#define DEBUG_RUNTIMEBOX

#ifdef DEBUG_RUNTIMEBOX
#       include <iostream>
#endif

RuntimeBox::RuntimeBox(std::string name, Triple pos, double ang, Triple vel, double vrot, double sx, double sy, double sz):
        BBox(name, pos, ang, vel, vrot, sx, sy, sz)
{}

void RuntimeBox::draw() const {
        Triple c = this->pos;

        glPushMatrix();
                glColor4ub(128, 255, 128, 255);
                glScalef(this->sx, this->sy, this->sz);
                glCallList(cubo_simple);
        glPopMatrix();
}
