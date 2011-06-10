#include "Wander.hpp"
#include "Mobile.hpp"
#include "util.hpp"
#include "Phantom.hpp"

Wander::Wander(Mobile *character  ,
               double maxRotation ,
               double targetRadius,
               double slowRadius  ,
               double wanderOffset,
               double wanderRadius,
               double wanderRate  ,
               double wanderTime  ,
               double maxSpeed    ) {
        this->character    = character;
        this->target       = new Phantom();
        this->maxRotation  = maxRotation;
        this->targetRadius = targetRadius;
        this->slowRadius   = slowRadius;
        this->wanderOffset = wanderOffset;
        this->wanderRadius = wanderRadius;
        this->wanderRate   = wanderRate;
        this->wanderTime   = wanderTime;
        this->maxSpeed     = maxSpeed;
        this->accum        = wanderTime;

        wanderOrientation = RandBin(-1, 1) * M_PI;
        target->ang = character->ang + wanderOrientation;
        target->pos = character->pos + target->orientation() * wanderRadius;
}

pair<bool, Triple> Wander::getVelIncr(unsigned int ticks) {
        pair<bool, Triple> steering;
        Triple direction;
        double distance, targetSpeed;

        steering.first = true;

        direction = target->pos - character->pos;
        distance = direction.length();

        if ((accum += ticks) > wanderTime) accum = wanderTime;

        if (distance < targetRadius) {
                if (accum == wanderTime) {
                        wanderOrientation += RandBin(-1, 1) * wanderRate;
                        target->ang = character->ang + wanderOrientation;
                        target->pos = character->pos + target->orientation() * wanderRadius;
                        accum = 0;
                }

                steering.second = target->vel - character->vel;
                if (steering.second.length() > maxSpeed) {
                        steering.second.normalized();
                        steering.second *= maxSpeed;
                }
                return steering;
        }

        targetSpeed = maxSpeed - character->vel.dot(direction.normalized());
        if (distance < slowRadius) {
                targetSpeed *= (distance - targetRadius) / (slowRadius - targetRadius);
        }
        if (targetSpeed < 0) targetSpeed = 0;
        if (targetSpeed > maxSpeed) targetSpeed = maxSpeed;

        steering.second = direction.normalized() * targetSpeed;
        return steering;
}
