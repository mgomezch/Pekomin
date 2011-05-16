#include "Arrive.hpp"
#include "Mobile.hpp"

#define DEBUG_ARRIVE

#ifdef DEBUG_ARRIVE
#include <stdio.h>
#endif

/*
unsigned int Arrive::type() {
        return BEHAVIOR_ARRIVE;
}
*/

Arrive::Arrive(Mobile *character, Mobile *target, double maxAcceleration, double maxSpeed, double targetRadius, double slowRadius) {
        this->character       = character;
        this->target          = target;
        this->maxAcceleration = maxAcceleration;
        this->maxSpeed        = maxSpeed;
        this->targetRadius    = targetRadius;
        this->slowRadius      = slowRadius;
}

tuple<bool, Triple,double> Arrive::getVel() {
        tuple<bool, Triple,double> steering;
        Triple direction, targetVelocity;
        double distance, targetSpeed;

        get<0>(steering) = true;
        get<2>(steering) = 0;

        direction = target->pos - character->pos;
        distance = direction.length();

        if (distance < targetRadius) {
#ifdef DEBUG_ARRIVE
                printf("mobile %p: arrive distance = %f < %f = targetRadius\n", character, distance, targetRadius);
                printf("mobile %p: return target->vel = ", character);
                target->vel.print();
                printf("\n");
#endif
                get<1>(steering) = target->vel;
                if (get<1>(steering).length() > maxSpeed) {
                        get<1>(steering).normalize();
                        get<1>(steering) *= maxSpeed;
                }
                return steering;
        }

        if (distance >= slowRadius) {
#ifdef DEBUG_ARRIVE
                printf("mobile %p: arrive distance = %f >= %f = slowRadius\n", character, distance, slowRadius);
#endif
                targetSpeed = maxSpeed;
        } else {
#ifdef DEBUG_ARRIVE
                printf("mobile %p: arrive distance = %f < %f = slowRadius\n", character, distance, slowRadius);
#endif
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
