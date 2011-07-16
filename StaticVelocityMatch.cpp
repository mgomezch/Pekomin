#include <vector>

#include "Mobile.hpp"
#include "StaticVelocityMatch.hpp"
#include "Triple.hpp"

StaticVelocityMatch::StaticVelocityMatch(std::string name, Mobile *character, Mobile *target):
        DirectKinematicV(name),
        character(character),
        target(target)
{}

std::vector<Triple> StaticVelocityMatch::getVel(unsigned int ticks, unsigned int delta_ticks) {
        return std::vector<Triple>(1, target->vel);
}
