#include "RuntimePekomin.hpp"

#include "gl.hpp"
#include <GL/glut.h>

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
}

void RuntimePekomin::draw() {
        glPushMatrix();
                glBegin(GL_LINES);
                        glColor3ub(0, 0, 128);

                        glVertex3f(0, 0, 0);
                        glVertex3f(1, 2, 0);

                        glVertex3f( 0, 0, 0);
                        glVertex3f(-1, 2, 0);
                glEnd();
        glPopMatrix();
        glColor4ub(255, 0, 0, 255);
        glCallList(cubo);
/*
        glBegin(GL_LINES);
                glVertex3f(0, 0, 0);
                glVertex3f(2, 0, 0);
        glEnd();
*/
}

