#include <GL/glut.h>
#include <cmath>

#include "RuntimeBox.hpp"
#include "gl.hpp"

//#define DEBUG_RUNTIMEBOX

#ifdef DEBUG_RUNTIMEBOX
#include <iostream>
#endif

RuntimeBox::RuntimeBox(string name, Triple pos, double ang, Triple vel, double vrot, double sx, double sy, double sz):
        Box(name, pos, ang, vel, vrot, sx, sy, sz)
{}

void RuntimeBox::draw() {
        Triple c = this->pos;

        glPushMatrix();
                glColor4ub(128, 255, 128, 255);
                glScalef(this->sx, this->sy, this->sz);
                glCallList(cubo_simple);
        glPopMatrix();
}
