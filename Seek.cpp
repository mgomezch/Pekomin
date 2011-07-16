#include <vector>

#include "Mobile.hpp"
#include "Seek.hpp"
#include "Triple.hpp"

#define DEBUG_SEEK

#ifdef DEBUG_SEEK
#       include <iostream>
#endif

Seek::Seek(std::string name, Mobile *character, Mobile *target, double maxSpeed):
        DirectKinematicV(name),
        character(character),
        target(target),
        maxSpeed(maxSpeed)
{}

std::vector<Triple> Seek::getVel(unsigned int ticks, unsigned int delta_ticks) {
        Triple cp, tp;

        std::tie(cp, tp) = points(this->character, this->target);
        return std::vector<Triple>(1, (tp - cp).normalized() * maxSpeed);
}
