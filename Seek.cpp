#include <vector>

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

vector<Triple> Seek::getVel(unsigned int ticks) {
        Triple cp, tp;

        tie(cp, tp) = points(this->character, this->target);
        return vector<Triple>(1, (tp - cp).normalized() * maxSpeed);
}
