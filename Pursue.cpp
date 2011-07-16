#include <vector>

#include "Mobile.hpp"
#include "Pursue.hpp"
#include "Triple.hpp"

//#define DEBUG_PURSUE

#ifdef DEBUG_PURSUE
#include <iostream>
#endif

Pursue::Pursue(string name, Mobile *character, Mobile *target, double maxSpeed):
        DirectKinematicV(name),
        character(character),
        target(target),
        maxSpeed(maxSpeed)
{}

vector<Triple> Pursue::getVel(unsigned int ticks) {
        Triple steering;
        Triple direction;
        double distance, targetRadius = 2.0, speed, prediction;
        Triple cp, tp;

        if (character->vel.length() == 0) {
                return vector<Triple>();
        }

        tie(cp, tp) = points(this->character, this->target);
        direction = tp - cp;
        distance = direction.length();

        if (distance < targetRadius) {
                return vector<Triple>();
        }

        speed = character->vel.length();

        if (speed <= (distance / maxPrediction)) prediction = maxPrediction;
        else prediction = distance / speed;

        steering = (tp + target->vel * prediction - cp).normalized() * maxSpeed;

        return vector<Triple>(1, steering);
}
