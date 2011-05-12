#include "KinematicWander.hpp"
#include "Ent.hpp"
#include "util.hpp"

KinematicWander::KinematicWander(Ent *character, double maxSpeed, double maxRotation) {
        this->character   = character;
        this->maxSpeed    = maxSpeed;
        this->maxRotation = maxRotation;
}

tuple<bool, Triple, double> KinematicWander::getVelIncr() {
        tuple<bool, Triple, double> steering;
        get<1>(steering)  = character->orientation() * maxSpeed;
        get<2>(steering) = randomBinomial()         * maxRotation;

        return steering;
}
