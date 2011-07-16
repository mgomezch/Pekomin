#include <vector>

#include "Mobile.hpp"
#include "Triple.hpp"
#include "util.hpp"
#include "VelocityMatch.hpp"

VelocityMatch::VelocityMatch(std::string name, Mobile *character, Mobile *target, double maxSpeed):
        KinematicV(name),
        character(character),
        target(target),
        maxSpeed(maxSpeed)
{}

std::vector<Triple> VelocityMatch::getVelIncr(unsigned int ticks, unsigned int delta_ticks) {
        Triple steering;
        double targetVelocity;

        steering = target->vel - character->vel;
        targetVelocity = map_atan(steering.length());
        steering *= targetVelocity * 1.0 / timeToTarget;

        if (steering.length() > maxSpeed) {
                steering.normalize();
                steering *= maxSpeed;
        }

        return std::vector<Triple>(1, steering);
}
