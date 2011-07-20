#include <vector>

#include "Mobile.hpp"
#include "Follow.hpp"
#include "Triple.hpp"

#include "Arrive.hpp"

#define DEBUG_FOLLOW

#ifdef DEBUG_FOLLOW
#       include <iostream>
#endif

Follow::Follow(std::string name, Mobile *character, Mobile *target, double phantomOffset, double maxSpeed, double targetRadius, double slowRadius) :
        DirectKinematicV(name),
        character(character),
        target(target),
        marcus(Phantom()),
        phantomOffset(phantomOffset),
        arrive(new Arrive(name + "Arrive", character, &marcus, maxSpeed, targetRadius, slowRadius))
{}

Follow::~Follow() {
        delete this->arrive;
}

std::vector<Triple> Follow::getVel(unsigned int ticks, unsigned int delta_ticks) {

        marcus.pos = target->pos + target->orientation() * phantomOffset;

        return (arrive->getVel(ticks, delta_ticks));
}
