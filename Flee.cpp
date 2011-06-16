#include "Flee.hpp"
#include "Mobile.hpp"

#define DEBUG_FLEE

#ifdef DEBUG_FLEE
#include <iostream>
#endif

Flee::Flee(Mobile *character, Mobile *target, double maxSpeed, double fleeRadius) {
        this->character  = character;
        this->target     = target;
        this->maxSpeed   = maxSpeed;
        this->fleeRadius = fleeRadius;
}

pair<bool, Triple> Flee::getVel(unsigned int ticks) {
        pair<bool, Triple> steering;

        Triple cp, tp;
        tie(cp, tp) = points(character, target);

        steering.second = cp - tp;
        if (steering.second.length() < fleeRadius) {
                steering.first = true;
                steering.second.normalize();
                steering.second *= maxSpeed;
        }
        return steering;
}
