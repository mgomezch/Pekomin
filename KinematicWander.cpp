#include "KinematicWander.hpp"
#include "Ent.hpp"
#include "util.hpp"

/*
unsigned int KinematicWander::type() {
        return BEHAVIOR_KINEMATICWANDER;
}
*/

KinematicWander::KinematicWander(Ent *character, double maxSpeed, double maxRotation) {
        this->character   = character;
        this->maxSpeed    = maxSpeed;
        this->maxRotation = maxRotation;
}

tuple<bool, Triple, double> KinematicWander::getVelIncr() {
        tuple<bool, Triple, double> steering;
<<<<<<< HEAD
	get<0>(steering) = true;
        get<1>(steering)  = character->orientation() * maxSpeed;
=======

        get<0>(steering) = true;
        get<1>(steering) = character->orientation() * maxSpeed;
>>>>>>> e8cbdbbbe9057150760e0464ca17d570e363c331
        get<2>(steering) = randomBinomial()         * maxRotation;

        return steering;
}
