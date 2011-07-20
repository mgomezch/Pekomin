#include "Odor.hpp"

#include "gl.hpp"
#include <GL/glut.h>

Odor::Odor(std::string name, Triple pos, unsigned int lifetime, double intensity, double spread):
        Ent(name, pos),
        lifetime(lifetime),
        intensity(intensity),
        spread(spread),
        accum(0)
{}

void Odor::draw() {
        double s = 10.0*(spread*static_cast<double>(this->accum))/static_cast<double>(this->lifetime);
        glPushMatrix();
                glColor4ub(0, 255, 0, 255 - static_cast<int>(255.0*static_cast<double>(this->accum))/static_cast<double>(this->lifetime));
                // TODO: no usar glutSolidSphere!!!
                glScalef(s, s, 0.2);
                glutSolidSphere(0.5, 16, 4);
#if 0
                glCallList(cubo);
                glBegin(GL_LINES);
                        glVertex3f(0, 0, 0);
                        glVertex3f(2, 0, 0);
                glEnd();
#endif
        glPopMatrix();
}

void Odor::steer(unsigned int ticks, unsigned int delta_ticks) {
        if ((this->accum += delta_ticks) >= lifetime) {
                this->dead = true;
        }
}

void Odor::update() {}
