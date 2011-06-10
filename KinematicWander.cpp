#include "KinematicWander.hpp"
#include "Ent.hpp"
#include "util.hpp"

KinematicWander::KinematicWander(Ent *character, double maxSpeed, double maxRotation) {
        this->character   = character;
        this->maxSpeed    = maxSpeed;
        this->maxRotation = maxRotation;
        this->accum       = 0;
}

pair<bool, Triple> KinematicWander::getVelIncr(unsigned int ticks) {
        pair<bool, Triple> steering;

        if (this->accum == 0) {
                steering.second = randomBinomial() * maxRotation;
        }
        if ((this->accum += ticks) >= 5000) this->accum = 0;

        steering.first = true;
        steering.second = character->orientation() * maxSpeed;
        steering.second = randomBinomial()         * maxRotation;

        return steering;
}
