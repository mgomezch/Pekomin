#include "Mobile.hpp"
#include "Seek.hpp"
#include "Triple.hpp"

#define DEBUG_SEEK

#ifdef DEBUG_SEEK
#       include <iostream>
#endif

Seek::Seek(string name, Mobile *character, Mobile *target, double maxSpeed):
        DirectKinematicV(name),
        character(character),
        target(target),
        maxSpeed(maxSpeed)
{}

pair<bool, Triple> Seek::getVel(unsigned int ticks) {
        pair<bool, Triple> steering;
        Triple cp, tp;

#if 0
        steering.first = true;
        steering.second = target->pos - character->pos;
        steering.second.normalize();
        steering.second *= maxSpeed;
#endif

        steering.first = true;
        tie(cp, tp) = points(this->character, this->target);
        steering.second = tp - cp;
        steering.second.normalize();
        steering.second *= maxSpeed;

        return steering;
}
