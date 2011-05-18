#include "Arrive.hpp"
#include "Mobile.hpp"

#define DEBUG_ARRIVE

#ifdef DEBUG_ARRIVE
#include <stdio.h>
#endif

Arrive::Arrive(Mobile *character, Mobile *target, double maxAcceleration, double maxSpeed, double targetRadius, double slowRadius) {
        this->character       = character;
        this->target          = target;
        this->maxAcceleration = maxAcceleration;
        this->maxSpeed        = maxSpeed;
        this->targetRadius    = targetRadius;
        this->slowRadius      = slowRadius;
}

tuple<bool, Triple, double> Arrive::getVel(unsigned int ticks) {
        tuple<bool, Triple, double> steering;
        Triple direction, targetVelocity;
        double distance, targetSpeed;

        get<0>(steering) = true;
        get<2>(steering) = 0;

        direction = target->pos - character->pos;
        distance = direction.length();

        if (distance < targetRadius) {
                target->vel.print();
                get<1>(steering) = target->vel;
                if (get<1>(steering).length() > maxSpeed) {
                        get<1>(steering).normalize();
                        get<1>(steering) *= maxSpeed;
                }
                return steering;
        }

        if (distance >= slowRadius) {
                targetSpeed = maxSpeed;
        } else {
                targetSpeed = maxSpeed * (distance - targetRadius) / (slowRadius - targetRadius);
        }

        get<1>(steering) = direction.normalized() * targetSpeed;

/*
        targetVelocity = direction.normalized() * targetSpeed;
        get<1>(steering) = (targetVelocity - character->vel) / timeToTarget;

        if (get<1>(steering).length() > maxAcceleration) {
                get<1>(steering).normalize();
                get<1>(steering) *= maxAcceleration;
        }
 */

        return steering;
}
