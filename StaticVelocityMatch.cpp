#include <vector>

#include "Mobile.hpp"
#include "StaticVelocityMatch.hpp"
#include "Triple.hpp"

StaticVelocityMatch::StaticVelocityMatch(string name, Mobile *character, Mobile *target):
        DirectKinematicV(name),
        character(character),
        target(target)
{}

vector<Triple> StaticVelocityMatch::getVel(unsigned int ticks) {
        return vector<Triple>(1, target->vel);
}
