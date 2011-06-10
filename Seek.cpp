#include "Seek.hpp"
#include "Mobile.hpp"

Seek::Seek(Mobile *character, Mobile *target, double maxAcceleration) {
        this->character       = character;
        this->target          = target;
        this->maxAcceleration = maxAcceleration;
}

pair<bool, Triple> Seek::getVelIncr(unsigned int ticks) {
        pair<bool, Triple> steering;

        steering.first = true;
        steering.second = target->pos - character->pos;
        steering.second.normalize();
        steering.second *= maxAcceleration;

        return steering;
}
