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

void RuntimeBox::addBehavior(Behavior *b) {
        behaviors.push_back(b);
#ifdef DEBUG_RUNTIMEBOX
        cout << "RuntimeBox " << static_cast<void *>(this) << ": adding behavior " << static_cast<void *>(b) << endl;
#endif
}

void RuntimeBox::draw() {
        Triple c = this->pos;

        glPushMatrix();
                glColor4ub(128, 255, 128, 255);
                glTranslatef(0, 0, 0.5);
                glTranslatef(c.x, c.y, c.z);
                glRotatef((this->ang * 180.0)/M_PI, 0, 0, 1);
                glScalef(this->sx, this->sy, this->sz);
                glCallList(cubo);
        glPopMatrix();
}
