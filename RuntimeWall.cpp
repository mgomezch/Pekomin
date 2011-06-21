#include <GL/glut.h>
#include <cmath>

#include "RuntimeWall.hpp"
#include "gl.hpp"

//#define DEBUG_RUNTIMEWALL

#ifdef DEBUG_RUNTIMEWALL
#include <iostream>
#endif

RuntimeWall::RuntimeWall() {
        this->pos  = Triple(0, 0, 0);
        this->ang  = 0;
        this->vel  = Triple(0, 0, 0);
        this->vrot = 0;
        this->p1   = Triple(0, 0, 0);
        this->p2   = Triple(0, 0, 0);
}
RuntimeWall::RuntimeWall(Triple p1, Triple p2) {
        this->pos  = Triple(0, 0, 0);
        this->ang  = 0;
        this->vel  = Triple(0, 0, 0);
        this->vrot = 0;
        this->p1   = p1;
        this->p2   = p2;
}

RuntimeWall::RuntimeWall(Triple pos, double ang) {
        this->pos  = pos;
        this->ang  = ang;
        this->vel  = Triple(0, 0, 0);
        this->vrot = 0;
        this->p1   = Triple(0, 0, 0);
        this->p2   = Triple(0, 0, 0);
}

RuntimeWall::RuntimeWall(Triple pos, double ang, Triple vel, double vang) {
        this->pos  = pos;
        this->ang  = ang;
        this->vel  = vel;
        this->vrot = vrot;
        this->p1   = Triple(0, 0, 0);
        this->p2   = Triple(0, 0, 0);
}

RuntimeWall::RuntimeWall(Triple pos, double ang, Triple p1, Triple p2) {
        this->pos  = pos;
        this->ang  = ang;
        this->vel  = Triple(0, 0, 0);
        this->vrot = 0;
        this->p1   = p1;
        this->p2   = p2;
}

RuntimeWall::RuntimeWall(Triple pos, double ang, Triple vel, double vang, Triple p1, Triple p2) {
        this->pos  = pos;
        this->ang  = ang;
        this->vel  = vel;
        this->vrot = vrot;
        this->p1   = p1;
        this->p2   = p2;
}

void RuntimeWall::addBehavior(Behavior *b) {
        behaviors.push_back(b);
#ifdef DEBUG_RUNTIMEWALL
        cout << "RuntimeWall " << static_cast<void *>(this) << ": adding behavior " << static_cast<void *>(b) << endl;
#endif
}

void RuntimeWall::draw() {
        Triple d = (p2 - p1);
        Triple c = (p1 + p2)/2.0;
        double s = d.length();

        glPushMatrix();
                glColor4ub(0, 126, 234, 128);
                glTranslatef(0, 0, 0.5);
                glBegin(GL_LINES);
                        glVertex3f(0, 0, 0);
                        glVertex3f(2, 0, 0);
                glEnd();
                glTranslatef(c.x, c.y, c.z);
                glRotatef((atan2(d.y, d.x)*180.0)/M_PI, 0, 0, 1);
                glScalef(s, width, height);
                glCallList(cubo);
        glPopMatrix();
}
