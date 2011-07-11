#include "Alien.hpp"
#include "Families.hpp"
#include "Behaviors.hpp"
#include "Triple.hpp"
#include "game.hpp"
#include "util.hpp"
#include "gl.hpp"

//#define DEBUG_ALIEN

#ifndef DEBUG_ALIEN
#include <iostream>
#endif

using namespace std;

Alien::Alien(string name, Triple pos, double ang, Triple vel, double vrot):
        Actor(name, pos, ang, vel, vrot) {
        this->hp    = 100;
        this->state = States::WANDER;
        this->wanderFlag = &addBehavior(new Wander(this, 0.2, 0.25, 1, 1, 7, 3.1415, 1000, 0.025));
        this->arriveFlag = &addBehavior(new Arrive(this, player, 0.015, 5, 10));
        this->arriveFlag->active = false;
        this->pursueFlag = &addBehavior(new Pursue(this, player, 0.0025));
        this->pursueFlag->active = false;
        this->evadeFlag  = &addBehavior(new Evade (this, player, 0.0025));
        this->evadeFlag->active  = false;
#ifdef DEBUG_ALIEN
        cout << "wanderFlag value: " << (this->wanderFlag)->active << endl;
        cout << "arriveFlag value: " << (this->arriveFlag)->active << endl;
        cout << "pursueFlag value: " << (this->pursueFlag)->active << endl;
        cout << "evadeFlag value: "  << (this->evadeFlag )->active << endl;
#endif
        for (unsigned int i = 0; i < ents.size(); i++) {
                if (this != dynamic_cast<Alien *>(ents[i])) {
                        (this->flock).push_back(&addBehavior(new Separation(this, dynamic_cast<Mobile *>(ents[i]), 0.05, 3)));
                        cout << "Flee : " << flock[i]->active << endl;
                }
        }
}

void Alien::steer(unsigned int ticks) {
        Triple cp, tp;

        tie(cp, tp) = points(this, player);

        if (state != States::WANDER && (tp - cp).length() > 20) {
                this->state = States::WANDER;
                (this->arriveFlag)->active = false;
                (this->evadeFlag )->active = false;
                (this->wanderFlag)->active = true ;
        }
        else if (state != States::ARRIVE && (tp - cp).length() <= 20) {
                this->state = States::ARRIVE;
                if (this->hp >= 40) {
                        (this->arriveFlag)->active = true ;
                        (this->evadeFlag )->active = false;
                        (this->wanderFlag)->active = false;
                }
                else {
                        (this->arriveFlag)->active = false;
                        (this->evadeFlag )->active = true ;
                        (this->wanderFlag)->active = false;
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
