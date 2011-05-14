#include "Flee.hpp"
#include "Mobile.hpp"

unsigned int Flee::type() {
        return BEHAVIOR_FLEE;
}

Flee::Flee(Mobile *character, Mobile *target, double maxAcceleration) {
        this->character       = character;
        this->target          = target;
        this->maxAcceleration = maxAcceleration;
}

tuple<bool, Triple,double> Flee::getVelIncr() {
        tuple<bool, Triple,double> steering;

        get<0>(steering) = true;
        get<1>(steering) = character->pos - target->pos;
        get<1>(steering).normalize();
        get<1>(steering) *= maxAcceleration;
        get<2>(steering) = 0;

        return steering;
}
