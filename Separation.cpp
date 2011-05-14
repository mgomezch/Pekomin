#include "Separation.hpp"
#include "Mobile.hpp"

#define MIN(X, Y)  ((X) < (Y) ? (X) : (Y))

unsigned int Separation::type() {
        return BEHAVIOR_SEPARATION;
}

Separation::Separation(Mobile *character, Mobile *target, double threshold, double decayCoefficient, double maxAcceleration) {
        this->character        = character;
        this->target           = target;
        this->threshold        = threshold;
        this->decayCoefficient = decayCoefficient;
        this->maxAcceleration  = maxAcceleration;
}

tuple<bool, Triple, double> Separation::getVelIncr() {
        tuple<bool, Triple, double> steering;
        double distance, strength;

        get<1>(steering) = target->pos - character->pos;
        distance = get<1>(steering).length();

        if (distance < threshold) {
                strength = MIN(decayCoefficient / (distance * distance), maxAcceleration);
                get<1>(steering).normalize();
                get<1>(steering) *= strength;
        }

        return steering;
}
