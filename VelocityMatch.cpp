#include "VelocityMatch.hpp"
#include "Mobile.hpp"
#include "util.hpp"

VelocityMatch::VelocityMatch(Mobile *character, Mobile *target, double maxSpeed) {
        this->character = character;
        this->target    = target;
        this->maxSpeed  = maxSpeed;
}

pair<bool, Triple> VelocityMatch::getVelIncr(unsigned int ticks) {
        pair<bool, Triple> steering;
        double targetVelocity;        

        steering.first = true;
        steering.second = target->vel - character->vel;
        targetVelocity = map_atan(steering.second.length());
        steering.second *= targetVelocity * 1.0 / timeToTarget;

        if (steering.second.length() > maxSpeed) {
                steering.second.normalize();
                steering.second *= maxSpeed;
        }

        return steering;
}
