#include "RuntimePekomin.hpp"

#include "gl.hpp"
#include <GL/glut.h>

//#define DEBUG_RUNTIMEPEKOMIN

#ifdef DEBUG_RUNTIMEPEKOMIN
#include <iostream>
#endif

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
#ifdef DEBUG_RUNTIMEPEKOMIN
        cout << "actor " << static_cast<void *>(this) << ": adding behavior " << static_cast<void *>(b) << endl;
#endif
}

void RuntimePekomin::draw() {
        glPushMatrix();
                glColor4ub(255, 0, 0, 255);
                glTranslatef(0, 0, 0.5);
                glCallList(cubo);
                glBegin(GL_LINES);
                        glVertex3f(0, 0, 0);
                        glVertex3f(2, 0, 0);
                glEnd();
        glPopMatrix();
}
