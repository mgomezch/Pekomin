#include <cmath>
#include <vector>

#include "Mobile.hpp"
#include "Phantom.hpp"
#include "Triple.hpp"
#include "util.hpp"
#include "Wander.hpp"

Wander::Wander(std::string name, Mobile *character, double maxRotation, double targetRadius, double slowRadius, double wanderOffset, double wanderRadius, double wanderRate, double wanderTime, double maxSpeed):
        DirectKinematicV(name),
        character(character),
        maxRotation(maxRotation),
        targetRadius(targetRadius),
        slowRadius(slowRadius),
        wanderOffset(wanderOffset),
        wanderRadius(wanderRadius),
        wanderRate(wanderRate),
        wanderTime(wanderTime),
        maxSpeed(maxSpeed),

        target(new Phantom()),
        accum(wanderTime),
        wanderOrientation(RandBin(-1, 1) * M_PI)
{
        target->ang = character->ang + wanderOrientation;
        target->pos = character->pos + target->orientation() * wanderRadius;
}

std::vector<Triple> Wander::getVel(unsigned int ticks, unsigned int delta_ticks) {
        Triple steering;
        Triple direction;
        double distance, targetSpeed;

        Triple cp, tp;
        std::tie(cp, tp) = points(character, target);

        direction = tp - cp;
        distance = direction.length();

        if ((accum += delta_ticks) >= wanderTime) {
                wanderOrientation += RandBin(-1, 1) * wanderRate;
                target->ang = character->ang + wanderOrientation;
                target->pos = cp + target->orientation() * wanderRadius;
                accum = 0;
        }

        if (distance < targetRadius) {
                steering = target->vel - character->vel;
                if (steering.length() > maxSpeed) {
                        steering.normalized();
                        steering *= maxSpeed;
                }
                return std::vector<Triple>(1, steering);
        }

        targetSpeed = maxSpeed - character->vel.dot(direction / distance);
        if (distance < slowRadius) {
                targetSpeed *= (distance - targetRadius) / (slowRadius - targetRadius);
        }
        if (targetSpeed < 0) targetSpeed = 0;
        if (targetSpeed > maxSpeed) targetSpeed = maxSpeed;

        steering = (direction * targetSpeed)/distance;
        return std::vector<Triple>(1, steering);
}
