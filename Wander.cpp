#include <cmath>

#include "Mobile.hpp"
#include "Phantom.hpp"
#include "Triple.hpp"
#include "util.hpp"
#include "Wander.hpp"

Wander::Wander(
                Mobile *character,
                double maxRotation,
                double targetRadius,
                double slowRadius,
                double wanderOffset,
                double wanderRadius,
                double wanderRate,
                double wanderTime,
                double maxSpeed
              ) {
        this->character    = character    ;
        this->target       = new Phantom();
        this->maxRotation  = maxRotation  ;
        this->targetRadius = targetRadius ;
        this->slowRadius   = slowRadius   ;
        this->wanderOffset = wanderOffset ;
        this->wanderRadius = wanderRadius ;
        this->wanderRate   = wanderRate   ;
        this->wanderTime   = wanderTime   ;
        this->maxSpeed     = maxSpeed     ;
        this->accum        = wanderTime   ;

        wanderOrientation = RandBin(-1, 1) * M_PI;
        target->ang = character->ang + wanderOrientation;
        target->pos = character->pos + target->orientation() * wanderRadius;
}

pair<bool, Triple> Wander::getVel(unsigned int ticks) {
        pair<bool, Triple> steering;
        Triple direction;
        double distance, targetSpeed;

        steering.first = true;

        Triple cp, tp;
        tie(cp, tp) = points(character, target);

        direction = tp - cp;
        distance = direction.length();

        if ((accum += ticks) > wanderTime) accum = wanderTime;

        if (accum == wanderTime) {
                wanderOrientation += RandBin(-1, 1) * wanderRate;
                target->ang = character->ang + wanderOrientation;
                target->pos = cp + target->orientation() * wanderRadius;
                accum = 0;
        }

        if (distance < targetRadius) {
                steering.second = target->vel - character->vel;
                if (steering.second.length() > maxSpeed) {
                        steering.second.normalized();
                        steering.second *= maxSpeed;
                }
                return steering;
        }

        targetSpeed = maxSpeed - character->vel.dot(direction / distance);
        if (distance < slowRadius) {
                targetSpeed *= (distance - targetRadius) / (slowRadius - targetRadius);
        }
        if (targetSpeed < 0) targetSpeed = 0;
        if (targetSpeed > maxSpeed) targetSpeed = maxSpeed;

        steering.second = (direction * targetSpeed)/distance;
        return steering;
}
