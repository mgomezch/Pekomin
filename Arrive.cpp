#include "Arrive.hpp"
#include "Mobile.hpp"

//#define DEBUG_ARRIVE

#ifdef DEBUG_ARRIVE
#include <stdio.h>
#endif

Arrive::Arrive(Mobile *character, Mobile *target, double maxSpeed, double targetRadius, double slowRadius) {
        this->character       = character;
        this->target          = target;
        this->maxSpeed        = maxSpeed;
        this->targetRadius    = targetRadius;
        this->slowRadius      = slowRadius;
}

pair<bool, Triple> Arrive::getVelIncr(unsigned int ticks) {
        pair<bool, Triple> steering;
        Triple direction, targetVelocity;
        double distance, targetSpeed;

        steering.first = true;

        direction = target->pos - character->pos;
        distance = direction.length();

        if (distance < targetRadius) {
                steering.second = target->vel - character->vel;
                if (steering.second.length() > maxSpeed) { // TODO: es aceleración, no speed
                        steering.second.normalize();
                        steering.second *= maxSpeed;
                }
                return steering;
        }

        targetSpeed = maxSpeed - character->vel.dot(direction.normalized());
        if (distance < slowRadius) {
                targetSpeed *= (distance - targetRadius) / (slowRadius - targetRadius);
        }
        if (targetSpeed < 0       ) targetSpeed = 0       ;
        if (targetSpeed > maxSpeed) targetSpeed = maxSpeed;

        steering.second = direction.normalized() * targetSpeed;

        return steering;
}
