#include "Pursue.hpp"
#include "Mobile.hpp"

Pursue::Pursue(Mobile *character, Mobile *target, double maxAcceleration) {
        this->character       = character;
        this->target          = target;
        this->maxAcceleration = maxAcceleration;
}

tuple<bool, Triple, double> Pursue::getVelIncr(unsigned int ticks) {
        tuple<bool, Triple, double> steering;
        Triple direction;
        double distance, speed, prediction;

        direction = target->pos + target->vel - character->pos;
        distance = direction.length();
        speed = character->vel.length();

        if (speed <= distance / maxPrediction) {
                prediction = maxPrediction;
        } else {
                prediction = distance / speed;
        }

        get<0>(steering) = true;
	get<2>(steering) = 0;
	
       	get<1>(steering) = direction * prediction;
       	get<1>(steering).normalize();
       	get<1>(steering) *= maxAcceleration;

        return steering;
}
