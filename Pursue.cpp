#include "Pursue.hpp"
#include "Mobile.hpp"

//#define DEBUG_PURSUE

#ifdef DEBUG_PURSUE
#include <iostream>
#endif

Pursue::Pursue(Mobile *character, Mobile *target, double maxSpeed) {
        this->character = character;
        this->target    = target   ;
        this->maxSpeed  = maxSpeed ;
        this->dead      = false    ;
}

pair<bool, Triple> Pursue::getVel(unsigned int ticks) {
        pair<bool, Triple> steering;
        Triple direction;
        double distance, targetRadius = 2.0, speed, prediction;
        Triple cp, tp;

        if (character->vel.length() == 0) {
                steering.first = false;
                return steering;
        }

        tie(cp, tp) = points(this->character, this->target);
        direction = tp - cp;
        distance = direction.length();

        if (distance < targetRadius) {
                steering.first = false;
                return steering;
        }

        speed = character->vel.length();

        if (speed <= (distance / maxPrediction)) prediction = maxPrediction;
        else prediction = distance / speed;

        steering.first = true;
        steering.second = (tp + target->vel * prediction - cp).normalized() * maxSpeed;

        return steering;
}
