#include "Mobile.hpp"
#include "StaticVelocityMatch.hpp"
#include "Triple.hpp"

StaticVelocityMatch::StaticVelocityMatch(string name, Mobile *character, Mobile *target):
        DirectKinematicV(name),
        character(character),
        target(target)
{}

pair<bool, Triple> StaticVelocityMatch::getVel(unsigned int ticks) {
        pair<bool, Triple> steering;

        steering.first = true;
        steering.second = target->vel;

        return steering;
}
