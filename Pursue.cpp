#include "Pursue.hpp"
#include "Mobile.hpp"

Pursue::Pursue(Mobile *character, Mobile *target, double maxAcceleration) {
        this->character       = character;
        this->target          = target;
        this->maxAcceleration = maxAcceleration;
}

pair<bool, Triple> Pursue::getVelIncr(unsigned int ticks) {
        pair<bool, Triple> steering;
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

        steering.first = true;

        steering.second = direction * prediction;
        steering.second.normalize();
        steering.second *= maxAcceleration;

        return steering;
}
