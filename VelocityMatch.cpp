#include "VelocityMatch.hpp"
#include "Mobile.hpp"

VelocityMatch::VelocityMatch(Mobile *character, Mobile *target, double maxAcceleration) {
        this->character       = character;
        this->target          = target;
        this->maxAcceleration = maxAcceleration;
}

pair<bool, Triple> VelocityMatch::getVelIncr(unsigned int ticks) {
        pair<bool, Triple> steering;

        steering.first = true;
        steering.second = target->vel - character->vel;
        steering.second /= timeToTarget;

        if (steering.second.length() > maxAcceleration) {
                steering.second.normalize();
                steering.second *= maxAcceleration;
        }

        return steering;
}
