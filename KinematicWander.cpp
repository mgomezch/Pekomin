#include "KinematicWander.hpp"
#include "Ent.hpp"
#include "util.hpp"

KinematicWander::KinematicWander(Ent *character, double maxSpeed, double maxRotation) {
        this->character   = character;
        this->maxSpeed    = maxSpeed;
        this->maxRotation = maxRotation;
        this->accum       = 0;
}

tuple<bool, Triple, double> KinematicWander::getVelIncr(unsigned int ticks) {
        tuple<bool, Triple, double> steering;

        if (this->accum == 0) {
                get<2>(steering) = randomBinomial() * maxRotation;
        }
        if ((this->accum += ticks) >= 3000) this->accum = 0;

        get<0>(steering) = true;
        get<1>(steering) = character->orientation() * maxSpeed;
        get<2>(steering) = randomBinomial()         * maxRotation;

        return steering;
}
