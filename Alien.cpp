#include <GL/glut.h>

#include "gl.hpp"
#include "Alien.hpp"
#include "Triple.hpp"

//#define DEBUG_ALIEN

#ifndef DEBUG_ALIEN
#       include <iostream>
#endif

Alien::Alien(std::string name, Triple pos, double ang, Triple vel, double vrot, int hpmax):
        Actor(name, pos, ang, vel, vrot),
        hpmax(hpmax),
        hp(hpmax)
{}

void Alien::draw() {
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
