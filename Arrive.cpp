#include <vector>

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

vector<Triple> Arrive::getVel(unsigned int ticks) {
        Triple steering;
        Triple direction, targetVelocity;
        double distance, targetSpeed;
        Triple cp, tp;

        tie(cp, tp) = points(this->character, this->target);
        direction = tp - cp;
        distance = direction.length();
        direction.normalize();

        if (distance < targetRadius) {
                steering = target->vel;
                if (steering.length() > maxSpeed) {
                        steering.normalize();
                        steering *= maxSpeed;
                }
                return vector<Triple>(1, steering);
        }

//      targetSpeed = maxSpeed - character->vel.dot(direction);
        targetSpeed = maxSpeed;
        if (distance < slowRadius) {
                targetSpeed *= (distance - targetRadius) / (slowRadius - targetRadius);
        }
//      if (targetSpeed < 0       ) targetSpeed = 0       ;
//      if (targetSpeed > maxSpeed) targetSpeed = maxSpeed;

        steering = direction * targetSpeed;

        return vector<Triple>(1, steering);
}
