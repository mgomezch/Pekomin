#include "Seek.hpp"
#include "Mobile.hpp"

/*
unsigned int Seek::type() {
        return BEHAVIOR_SEEK;
}
*/

Seek::Seek(Mobile *character, Mobile *target, double maxAcceleration) {
        this->character       = character;
        this->target          = target;
        this->maxAcceleration = maxAcceleration;
}

tuple<bool, Triple, double> Seek::getVelIncr() {
        tuple<bool, Triple, double> steering;

        get<0>(steering) = true;
        get<1>(steering) = target->pos - character->pos;
        get<1>(steering).normalize();
        get<1>(steering) *= maxAcceleration;
        get<2>(steering) = 0;

        return steering;
}
