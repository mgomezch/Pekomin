#include "KinematicWander.hpp"
#include "Ent.hpp"
#include "util.hpp"

KinematicWander::KinematicWander(Ent *character_, double maxSpeed_, double maxRotation_) {
        character   = character_;
        maxSpeed    = maxSpeed_;
        maxRotation = maxRotation_;
}

pair<Triple,double> KinematicWander::getSteering() {
        pair<Triple, double> steering;
        steering.first  = character->orientation() * maxSpeed;
        steering.second = randomBinomial()         * maxRotation;

        return steering;
}

string KinematicWander::name() {
	return "KinematicWander";
}
