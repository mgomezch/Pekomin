#include "KinematicWander.hpp"

KinematicWander::KinematicWander(Ent character, double maxSpeed, double maxRotation) {
        character   = character;
        maxSpeed    = maxSpeed;
        maxRotation = maxRotation;
}

pair<Triple,double> KinematicWander::getSteering() {
        pair<Triple,double> steering;
        steering.first  = character.pos()  * maxSpeed;
        steering.second = randomBinomial() * maxRotation;

        return steering;
}
