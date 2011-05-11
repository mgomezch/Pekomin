#include "KinematicWander.hpp"
#include "Ent.hpp"
#include "util.hpp"

KinematicWander::KinematicWander(Ent *character, double maxSpeed, double maxRotation) {
        this->character   = character;
        this->maxSpeed    = maxSpeed;
        this->maxRotation = maxRotation;
}

pair<Triple, double> KinematicWander::getSteering() {
        pair<Triple, double> steering;
        steering.first  = character->orientation() * maxSpeed;
        steering.second = randomBinomial()         * maxRotation;

        return steering;
}
