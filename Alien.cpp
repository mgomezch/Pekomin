#include "Alien.hpp"
#include "gl.hpp"
#include "Triple.hpp"

#include "Arrive.hpp"
#include "Evade.hpp"
#include "Pursue.hpp"
#include "Wander.hpp"

//#define DEBUG_ALIEN

#ifndef DEBUG_ALIEN
#       include <iostream>
#endif

using namespace std;

Alien::Alien(Mobile *target, string name, Triple pos, double ang, Triple vel, double vrot, int hpmax):
        Actor(name, pos, ang, vel, vrot),
        target(target),
        hpmax(hpmax),
        hp(hpmax),
        state(States::Wander),
        wander(&addBehavior(new Wander(name + "Wander", this, 0.2, 0.25, 1, 1, 7, 3.1415, 1000, 0.025))),
        arrive(&addBehavior(new Arrive(name + "Arrive", this, target, 0.015, 5, 10))),
        pursue(&addBehavior(new Pursue(name + "Pursue", this, target, 0.0025))),
        evade (&addBehavior(new Evade (name + "Evade" , this, target, 0.0025)))
{
#if 0
        this->wander = &addBehavior(new Wander(this, 0.2, 0.25, 1, 1, 7, 3.1415, 1000, 0.025));
        this->arrive = &addBehavior(new Arrive(this, target, 0.015, 5, 10));
        this->pursue = &addBehavior(new Pursue(this, target, 0.0025));
        this->evade  = &addBehavior(new Evade (this, target, 0.0025));
#endif

        this->arrive->active = false;
        this->pursue->active = false;
        this->evade ->active = false;
}

void Alien::steer(unsigned int ticks) {
        Triple cp, tp;
        double d;

        tie(cp, tp) = points(this, target);
        d = (tp - cp).length();

        if (state != States::Wander && d > 20) {
                this->state = States::Wander;
                this->wander->active = true ;
                this->arrive->active = false;
                this->pursue->active = false;
                this->evade ->active = false;
        }
        else if (state != States::Arrive && d <= 20) {
                this->state = States::Arrive;
                if (this->hp >= 40) {
                        this->wander->active = false;
                        this->arrive->active = true ;
                        this->pursue->active = false;
                        this->evade ->active = false;
                }
                else {
                        this->wander->active = false;
                        this->arrive->active = false;
                        this->pursue->active = false;
                        this->evade ->active = true ;
                }
        }

        this->Actor::steer(ticks);
}

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
