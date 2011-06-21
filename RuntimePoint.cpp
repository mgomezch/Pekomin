#include "RuntimePoint.hpp"

#include "gl.hpp"
#include <GL/glut.h>

//#define DEBUG_RUNTIMEPOINT

#ifdef DEBUG_RUNTIMEPOINT
#include <iostream>
#endif

RuntimePoint::RuntimePoint(string name, Triple pos, double ang, Triple vel, double vrot):
        Actor(name, pos, ang, vel, vrot)
{}

void RuntimePoint::addBehavior(Behavior *b) {
        behaviors.push_back(b);
#ifdef DEBUG_RUNTIMEPOINT
        cout << "actor " << static_cast<void *>(this) << ": adding behavior " << static_cast<void *>(b) << endl;
#endif
}

void RuntimePoint::draw() {
        glPushMatrix();
                glColor4ub(255, 0, 0, 255);
                glTranslatef(0, 0, 0.5);
                glCallList(cubo_simple);
                glBegin(GL_LINES);
                        glVertex3f(0, 0, 0);
                        glVertex3f(2, 0, 0);
                glEnd();
        glPopMatrix();
}
