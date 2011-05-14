#include "Pursue.hpp"
#include "Mobile.hpp"

unsigned int Pursue::type() {
        return BEHAVIOR_PURSUE;
}

Pursue::Pursue(Mobile *character, Mobile *target, double maxAcceleration) {
        this->character       = character;
        this->target          = target;
        this->maxAcceleration = maxAcceleration;
}

tuple<bool, Triple, double> Pursue::getVelIncr() {
        tuple<bool, Triple, double> steering;
        Triple direction;
        double distance, speed, prediction;

        direction = target->pos - character->pos;
        distance = direction.length();
        speed = character->vel.length();

        if (speed <= distance / maxPrediction) {
                prediction = maxPrediction;
        } else {
                prediction = distance / speed;
        }

        get<0>(steering) = true;
        get<1>(steering) = target->pos + target->vel * prediction - character->pos;
        get<1>(steering).normalize();
        get<1>(steering) *= maxAcceleration;
        get<2>(steering) = 0;

        return steering;
}
