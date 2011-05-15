#include "Evade.hpp"
#include "Mobile.hpp"

/*
unsigned int Evade::type() {
        return BEHAVIOR_EVADE;
}
*/

Evade::Evade(Mobile *character, Mobile *target, double maxAcceleration) {
        this->character       = character;
        this->target          = target;
        this->maxAcceleration = maxAcceleration;
}

tuple<bool, Triple, double> Evade::getVelIncr() {
        tuple<bool, Triple, double> steering;
        Triple direction;
        double distance, speed, prediction;

        direction = character->pos - target->pos;
        distance = direction.length();
        speed = character->vel.length();

        if (speed <= distance / maxPrediction) {
                prediction = maxPrediction;
        } else {
                prediction = distance / speed;
        }

        get<0>(steering) = true;
        get<1>(steering) = character->pos - target->vel * prediction;
        get<1>(steering).normalize();
        get<1>(steering) *= maxAcceleration;
        get<2>(steering) = 0;

        return steering;
}
