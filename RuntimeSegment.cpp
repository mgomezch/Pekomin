#include <GL/glut.h>
#include <cmath>

#include "RuntimeSegment.hpp"
#include "gl.hpp"

//#define DEBUG_RUNTIMESEGMENT

#ifdef DEBUG_RUNTIMESEGMENT
#include <iostream>
#endif

RuntimeSegment::RuntimeSegment(string name, Triple pos, double ang, Triple vel, double vrot, Triple p1, Triple p2):
        Segment(name, pos, ang, vel, vrot, p1, p2)
{}

void RuntimeSegment::draw() {
        Triple d = (p2 - p1);
        Triple c = (p1 + p2)/2.0;
        double s = d.length();

        glPushMatrix();
                glColor4ub(255, 0, 0, 255);
                glTranslatef(0, 0, 0.5);
                glBegin(GL_LINES);
                        glVertex3f(0, 0, 0);
                        glVertex3f(2, 0, 0);
                glEnd();
                glTranslatef(c.x, c.y, c.z);
                glRotatef((atan2(d.y, d.x)*180.0)/M_PI, 0, 0, 1);
                glScalef(s, 0.2, 1);
                glCallList(cubo_simple);
        glPopMatrix();
}
