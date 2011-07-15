#include "Arrive.hpp"
#include "Mobile.hpp"
#include "Triple.hpp"

//#define DEBUG_ARRIVE

#ifdef DEBUG_ARRIVE
#include <iostream>
#endif

Arrive::Arrive(string name, Mobile *character, Mobile *target, double maxSpeed, double targetRadius, double slowRadius):
        DirectKinematicV(name),
        character(character),
        target(target),
        maxSpeed(maxSpeed),
        targetRadius(targetRadius),
        slowRadius(slowRadius)
{}

pair<bool, Triple> Arrive::getVel(unsigned int ticks) {
        pair<bool, Triple> steering;
        Triple direction, targetVelocity;
        double distance, targetSpeed;
        Triple cp, tp;

        steering.first = true;

        tie(cp, tp) = points(this->character, this->target);
        direction = tp - cp;
        distance = direction.length();
        direction.normalize();

        if (distance < targetRadius) {
                steering.second = target->vel;
                if (steering.second.length() > maxSpeed) {
                        steering.second.normalize();
                        steering.second *= maxSpeed;
                }
                return steering;
        }

//      targetSpeed = maxSpeed - character->vel.dot(direction);
        targetSpeed = maxSpeed;
        if (distance < slowRadius) {
                targetSpeed *= (distance - targetRadius) / (slowRadius - targetRadius);
        }
//      if (targetSpeed < 0       ) targetSpeed = 0       ;
//      if (targetSpeed > maxSpeed) targetSpeed = maxSpeed;

        steering.second = direction * targetSpeed;

        return steering;
}
