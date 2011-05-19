#include "Flee.hpp"
#include "Mobile.hpp"

Flee::Flee(Mobile *character, Mobile *target, double maxSpeed, double fleeRadius) {
        this->character  = character;
        this->target     = target;
        this->maxSpeed   = maxSpeed;
        this->fleeRadius = fleeRadius;
}

tuple<bool, Triple, double> Flee::getVelIncr(unsigned int ticks) {
        tuple<bool, Triple, double> steering;

        get<1>(steering) = character->pos - target->pos;
        if (get<1>(steering).length() < fleeRadius) {
                get<0>(steering) = true;
                get<1>(steering).normalize();
                get<1>(steering) *= maxSpeed;
                get<2>(steering) = 0;
        } else {
                get<0>(steering) = false;
        }
        return steering;
}
