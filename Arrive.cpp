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

tuple<bool, Triple, double> Arrive::getVelIncr(unsigned int ticks) {
        tuple<bool, Triple, double> steering;
        Triple direction, targetVelocity;
        double distance, targetSpeed;

        get<0>(steering) = true;
        get<2>(steering) = 0;

        direction = target->pos - character->pos;
        distance = direction.length();

        if (distance < targetRadius) {
                get<1>(steering) = target->vel - character->vel;
                if (get<1>(steering).length() > maxSpeed) { // TODO: es aceleración, no speed
                        get<1>(steering).normalize();
                        get<1>(steering) *= maxSpeed;
                }
                return steering;
        }

        targetSpeed = maxSpeed - character->vel.dot(direction.normalized());
        if (distance < slowRadius) {
                targetSpeed *= (distance - targetRadius) / (slowRadius - targetRadius);
        }
        if (targetSpeed < 0       ) targetSpeed = 0       ;
        if (targetSpeed > maxSpeed) targetSpeed = maxSpeed;

        get<1>(steering) = direction.normalized() * targetSpeed;

        return steering;
}
