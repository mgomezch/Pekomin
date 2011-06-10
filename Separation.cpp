#include "Separation.hpp"
#include "Mobile.hpp"

#define MIN(X, Y)  ((X) < (Y) ? (X) : (Y))

Separation::Separation(Mobile *character, Mobile *target, double threshold, double decayCoefficient, double maxAcceleration) {
        this->character        = character;
        this->target           = target;
        this->threshold        = threshold;
        this->decayCoefficient = decayCoefficient;
        this->maxAcceleration  = maxAcceleration;
}

pair<bool, Triple> Separation::getVelIncr(unsigned int ticks) {
        pair<bool, Triple> steering;
        double distance, strength;

        steering.first = true;
        steering.second = target->pos - character->pos;
        distance = steering.second.length();

        if (distance < threshold) {
                strength = MIN(decayCoefficient / (distance * distance), maxAcceleration);
                steering.second.normalize();
                steering.second *= strength;
        }

        return steering;
}
